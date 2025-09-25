import re
import os
import sys
import html
import stat
import shutil
import requests
import subprocess
from os import path
from re import Match
from time import time
from enum import IntEnum
from pathlib import Path
from requests import Response
from bs4 import BeautifulSoup, Tag
from argparse import ArgumentParser
from typing import Final, Callable, Any, Iterable
from concurrent.futures import ProcessPoolExecutor
from bs4.element import NavigableString, PageElement, AttributeValueList


VULKAN_VALID_USAGE: Final = "https://raw.githubusercontent.com/KhronosGroup/Vulkan-Registry/refs/heads/main/specs/latest/validation/validusage.json"
VULKAN_REGISTRY: Final    = "https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/"
VERSION_FILE: Final       = "./.version.txt"
NOT_PRINTED_DIVS: Final   = ["Document Notes", "See Also", "Copyright"]
CLONE_ARGS: Final         = ["--depth", "1", "--quiet", "-c", "advice.detachedHead=false"]
CHAR_FIX_MAP: Final       = {"\\rfloor": '⌋', "\\lfloor": '⌊', "\\times": '\u00D7', "\\(": '', "\\)": ''}
HEADERS_REPO_PATH: Final  = "./.hds"
REGISTRY_REPO_PATH: Final = "./.rex"
BLANK_CHAR: Final         = '\u2800'
FAKE_PIPE_CHAR: Final     = '\uFF5C'
FAKE_SLASH_CHAR: Final    = '\u29F8'
COMMENT_REGEX: Final      = re.compile(r"(\/\/.+)|(\/\*(.|\n)+?\*\/)")
DEFINITION_REGEX: Final   = re.compile(r" *#define (VK_[^\n (]+)")
HANDLE_REGEX: Final       = re.compile(r"^((VK_DEFINE_HANDLE\(([^\n)]+)\))\n|(VK_DEFINE_NON_DISPATCHABLE_HANDLE\(([^\n)]+)\))\n(?!```))", re.MULTILINE)
FUNCTION_REGEX: Final     = re.compile(r"^(VKAPI_ATTR [^\n ]+ VKAPI_CALL (vk[^ \n]+)\([^;]+);\n(?!```)", re.MULTILINE)
TYPEDEF_REGEX: Final      = re.compile(r"^(typedef [^ \n]+ (Vk[^ \n]+)( {\n[^}]+} [^;]+)?;\n(?!```))", re.MULTILINE)


class StyleFormatFlag(int):
    pass


class StyleFlag(int):
    def __getitem__(self: "StyleFlag", item: StyleFormatFlag) -> StyleFormatFlag:
        return StyleFormatFlag(int(item) << (int(self) * 0x4))


class StyleInfoFlags(int):
    pass


HTML     = StyleFormatFlag(0b01)
MARKDOWN = StyleFormatFlag(0b10)
DOXYGEN  = StyleFormatFlag(0b11)

BOLD        = StyleFlag(0)
ITALIC      = StyleFlag(1)
ITALIC_BOLD = StyleFlag(2)
SUBTEXT     = StyleFlag(3)
REFERENCE   = StyleFlag(4)
HEADER      = StyleFlag(5)
LIST        = StyleFlag(6)
TABLE       = StyleFlag(7)
PRE         = StyleFlag(8)
BREAK       = StyleFlag(9)
CODE        = StyleFlag(10)
DT          = StyleFlag(11)

REQUIRES_FAKE_BAR    = StyleInfoFlags(0x100000000000)
REQUIRES_FAKE_SPACES = StyleInfoFlags(0x200000000000)


class Style(IntEnum):
    TXT = REQUIRES_FAKE_SPACES
    CL  = BOLD[HTML]                \
          | ITALIC[HTML]            \
          | ITALIC_BOLD[HTML]       \
          | SUBTEXT[HTML]           \
          | REFERENCE[HTML]         \
          | LIST[HTML]              \
          | PRE[HTML]               \
          | BREAK[HTML]             \
          | CODE[DOXYGEN]           \
          | HEADER[HTML]            \
          | DT[HTML]
    RS  = BOLD[HTML]                \
          | ITALIC[HTML]            \
          | SUBTEXT[HTML]           \
          | REFERENCE[MARKDOWN]     \
          | LIST[MARKDOWN]          \
          | CODE[DOXYGEN]
    VSC = REFERENCE[MARKDOWN]       \
          | TABLE[MARKDOWN]         \
          | CODE[MARKDOWN]          \
          | HEADER[MARKDOWN]        \
          | REQUIRES_FAKE_BAR       \
          | REQUIRES_FAKE_SPACES
          # VSC supports BREAK[HTML] but it's not required ('\n' is shown in view)

    __edits: dict = {
        "bold": [None, ("<b>", "</b>"), ("**", "**"), None],
        "italic": [None, ("<i>", "</i>"), ("*", "*"), None],
        "italic_bold": [None, ("<b><i>", "</i></b>"), ("***", "***"), None],
        "pre": [None, ("<pre>", "</pre>"), None, ("@verbatim ", "@endverbatim")],
        "sub": [None, ("<sub>", "</sub>"), None, None],
        "h2": [None, ("<b>", "</b><hr>"), "## ", None],
        "h3": [None, ("<b>", "</b>"), "### ", None]
    }

    @property
    def space(self) -> str:
        return BLANK_CHAR if self & REQUIRES_FAKE_SPACES else ' '

    def __and__(self, other: Any) -> int:
        if isinstance(other, StyleFlag):
            return int(self) & (0x3 << other)
        return int(self) & int(other)

    def make_bold(self, text: str) -> str:
        if t := self.__edits["bold"][self.__idx(BOLD)]:
            return f"{t[0]}{text}{t[1]}"
        return text

    def make_italic(self, text: str) -> str:
        if t := self.__edits["italic"][self.__idx(ITALIC)]:
            return f"{t[0]}{text}{t[1]}"
        return text

    def make_bold_italic(self, text: str) -> str:
        if t := self.__edits["italic_bold"][self.__idx(ITALIC_BOLD)]:
            return f"{t[0]}{text}{t[1]}"
        return self.make_bold(text)

    def make_pre(self, text: str) -> str:
        if t := self.__edits["pre"][self.__idx(PRE)]:
            return f"{t[0]}{text}{t[1]}"
        return text

    def make_sub(self, text: str) -> str:
        if t := self.__edits["sub"][self.__idx(SUBTEXT)]:
            return f"{t[0]}{text}{t[1]}"
        return text

    def make_ref(self, text: str, url: str) -> str:
        if self.__check(REFERENCE, HTML):
            return f"<a href=\"{url}\">{text}</a>"
        if self.__check(REFERENCE, MARKDOWN):
            text = text if text != "" else "↖ "
            return f"[{text}]({url})"
        if self.__check(REFERENCE, DOXYGEN):
            raise Warning(f"Invalid flag REFERENCE[DOXYGEN] used in style '{self.name}'.")
        return text

    def make_header2(self, text: str) -> str:
        if t := self.__edits["h2"][self.__idx(HEADER)]:
            return f"{t[0]}{text}{t[1]}\n"
        return self.make_bold(text)

    def make_header3(self, text: str) -> str:
        if t := self.__edits["h3"][self.__idx(HEADER)]:
            return f"{t[0]}{text}{t[1]}\n"
        return self.make_bold(text)

    def make_break(self) -> str:
        if self.__check(BREAK, HTML):
            return f"<br>\n"
        if self.__check(BREAK, MARKDOWN):
            raise Warning(f"Invalid flag BREAK[MARKDOWN] used in style '{self.name}'.")
        if self.__check(BREAK, DOXYGEN):
            raise Warning(f"Invalid flag BREAK[DOXYGEN] used in style '{self.name}'.")
        return f"\n"

    def has_html_lists(self) -> bool:
        return self.__check(LIST, HTML)

    def make_list_entry(self, name: str, level: int) -> str:
        if self.__check(LIST, HTML):
            return f"{level * "    "}<{name}>"
        if self.__check(LIST, MARKDOWN):
            return f"{level * "  "}- "
        if self.__check(LIST, DOXYGEN):
            raise Warning(f"Invalid flag LIST[DOXYGEN] used in style '{self.name}'.")
        return f"- {level * self.space * 4}"

    def make_codeblock(self, prefix: str, level: int, text: str) -> str:
        if self.__check(CODE, HTML):
            raise Warning(f"Invalid flag CODE[HTML] used in style '{self.name}'.")
        if self.__check(CODE, MARKDOWN):
            spaces: str = self.space * 4 * level
            return f"```c\n{spaces}{text.replace('\n', f"\n{spaces}")}\n```\n"
        if self.__check(CODE, DOXYGEN):
            return f"{prefix}@code{{.c}}\n{prefix}{text.replace('\n', f"\n{prefix}")}\n{prefix}@endcode\n"
        return f"\n{prefix}{text.replace('\n', f"\n{prefix}")}\n{prefix}\n"

    def make_dt(self, text: str, prefix: str, level: int) -> str:
        if self.__check(DT, HTML):
            return f"{level * "    "}<dt><b>{text}</b>\n"
        if self.__check(DT, MARKDOWN):
            raise Warning(f"Invalid flag DT[MARKDOWN] used in style '{self.name}'.")
        if self.__check(DT, DOXYGEN):
            raise Warning(f"Invalid flag DT[DOXYGEN] used in style '{self.name}'.")
        if self.__check(HEADER, MARKDOWN):
            return f"{level * self.space * 2}#### {self.space}{text}\n" + \
                    f"{prefix}\n"
        return f"{level * self.space}{text}\n"

    def make_table(self, prefix: str, rows: list[list[str | None]], widths: list[int], columns: int) -> str:
        def format_line(lines: list[list[str]], line_idx: int, term) -> str:
            if self.__check(TABLE, HTML):
                raise Warning(f"Invalid flag TABLE[HTML] used in style '{self.name}'.")
            elif self.__check(TABLE, MARKDOWN):
                pipe: str = FAKE_PIPE_CHAR if self & REQUIRES_FAKE_BAR else ''
                line: str = f"{prefix}|{pipe} "

                for cell_idx, cell_lines in enumerate(lines):
                    text: str = (cell_lines[line_idx] if cell_lines[line_idx] is not None else '') if line_idx < len(cell_lines) else ''
                    sep: str  = FAKE_PIPE_CHAR if not cell_idx < len(lines) - 1 or (line_idx < len(lines[cell_idx + 1]) and lines[cell_idx + 1][line_idx] is not None) else ''
                    sep       = sep if self & REQUIRES_FAKE_BAR else ''
                    line     += f"{text} |{sep} "

                return line + '|'
            elif self.__check(TABLE, DOXYGEN):
                raise Warning(f"Invalid flag TABLE[DOXYGEN] used in style '{self.name}'.")

            line: str = f"{prefix}|  "

            for cell_idx, cell_lines in enumerate(lines):
                text: str = (cell_lines[line_idx] if cell_lines[line_idx] is not None else '') if line_idx < len(cell_lines) else ''
                sep: str  = '|' if not cell_idx < len(lines) - 1 or (line_idx < len(lines[cell_idx + 1]) and lines[cell_idx + 1][line_idx] is not None) else ' '
                line     += f"{text:<{widths[cell_idx] - 2}}  {sep}  "

            if self & REQUIRES_FAKE_SPACES:
                line = line.replace(' ', BLANK_CHAR)

            return line[:-2] + term

        def format_row(row: list[str | None], term: str) -> list[str]:
            # lines[cell_idx][line_idx], contains all the lines for each cell.
            lines: list = [str(cell).split("\n") if cell is not None else [None] for cell in row]
            indexes     = range(max(len(cell_lines) for cell_lines in lines))

            return [format_line(lines, idx, term) for idx in indexes]

        table: list   = []
        term: str     = ""
        line_sep: str = ""
        if not (self & TABLE):
            term     = "<br>" if self & BREAK[HTML] else ''
            line_sep = prefix + '-' * (sum(widths) + 3 * len(widths) + 1) + term
            table.append(line_sep)

        for row in rows:
            table.extend(format_row(row, term))
            if not (self & TABLE):
                table.append(line_sep)

        if self.__check(TABLE, MARKDOWN):
            table_align: str = prefix + "| :-- " * (columns + 1) + '|'
            table.insert(1, table_align)

        string: str = f"{'\n'.join(table)}\n{prefix}"
        return self.make_pre(string) + self.make_break() + prefix + '\n'

    def __idx(self, flag: StyleFlag) -> int:
        return (self & (0b11 << (flag * 0x4))) >> (flag * 0x4)

    def __check(self, flag: StyleFlag, mod: StyleFormatFlag) -> bool:
        return self.__idx(flag) == mod


class DocumentationBlock:
    def __init__(self, name: str, style: Style, indent: int) -> None:
        self.__value             = ""
        self.__style             = style
        self.__url               = f"{VULKAN_REGISTRY}{name}.html"
        self.__indentation_level = indent
        self.__prefix            = indent * "    " + " * " if style != Style.TXT else ''

        self.__add_dd          = self.__add_li if self.__style == Style.CL else self.__add_children
        self.__add_sectionbody = self.__add_children
        self.__add_dl          = self.__add_ul
        self.__add_title       = self.__add_h2

        if style == Style.TXT:
            self.__add_p = self.__optional_add_p

    def add(self, e: PageElement, line: bool = False, level: int = 0, name: str | None = None) -> None:
        def getprivattr(name: str) -> Callable[[Tag, bool, int], None] | None:
            return getattr(self, f"_{type(self).__name__}__add_{name}", None)

        if isinstance(e, NavigableString):
            self.__add_children(e, line, level)
            return

        if not isinstance(e, Tag):
            raise TypeError("Invalid element type.")

        if name:
            converter = getprivattr(name)
            if not converter:
                raise ValueError("Unsupported HTML element name.")

            converter(e, line, level)
            return

        name = e.name if e.name != "div" else ' '.join(e.get("class", AttributeValueList()))
        name = re.sub(r"[^a-zA-Z0-9_]", '_', name)

        converter = getprivattr(name)
        if converter:
            converter(e, line, level)
        else:
            self.__add_children(e, line, level)

    def empty(self) -> bool:
        return self.__value == ""

    @property
    def value(self) -> str:
        string: str = self.__value
        indent: int = self.indentation_level * 4
        empty: str  = rf" {{{indent + 1}}}\* "

        # Fix invalid chars
        for old, new in CHAR_FIX_MAP.items():
            string = string.replace(old, new)

        if self.style in [Style.CL, Style.RS]:
            # Remove break before code block
            string = re.sub(rf"(<br>)+(\n{empty}\n {{{indent + 1}}}\* @code)", r"\2", string)

            # Fix sub-text
            string = re.sub(r"(?<=[\s,.=])([a-zA-Z])_([a-zA-Z]+)(?=[\s,.=])", r"\1<sub>\2</sub>", string)
        else:
            def sub_text(match: Match[str]) -> str:
                return match.group(1).upper() + match.group(2)

            # Fix sub-text
            string = re.sub(r"(?<=[\s,.=])([a-zA-Z])_([a-zA-Z]+)(?=[\s,.=])", sub_text, string)

        if self.style.has_html_lists():
            string = string.replace("<li> ", "<li>")
            string = string.replace(f"{self.__prefix}</ul>\n{self.__prefix}\n{self.__prefix}<ul>\n", "")
            string = string.replace(f"{self.__prefix}</dl>\n{self.__prefix}\n{self.__prefix}<dl>\n", "")

        # Remove extra whitespace
        string = re.sub(rf"{empty}\n( {{{indent + 1}}}\* \n)", r"\1", string)
        string = re.sub(rf"(({empty})( {{4}})+)( +)?", r"\1", string)

        if self.style == Style.RS:
            string = re.sub(r"(@endcode[ \n*]+)<br>", r"\1", string)

        if self.style == Style.TXT:
            string = re.sub(rf"^ {{{indent}}} \* ", '', string, flags=re.MULTILINE)

        # Some documentation blocks may contain comments inside the @code blocks.
        string = string.replace("*/", f"*{FAKE_SLASH_CHAR}")
        string = string.replace("/*", f"{FAKE_SLASH_CHAR}*")

        prefix: str = f"{self.indentation_level * "    "}/**\n"
        suffix: str = f"{self.indentation_level * "    "}*/\n"

        # Documentation end
        if string[-3:] == "* \n":
            string = string[:-2] + "/\n"
        else:
            if string[-1] != '\n':
                string += '\n'
            string += suffix

        return prefix + string

    @property
    def url(self) -> str:
        return self.__url

    @property
    def style(self) -> Style:
        return self.__style

    @property
    def indentation_level(self) -> int:
        return self.__indentation_level

    def __add(self, text: str) -> None:
        self.__value += text

    def __suffix(self, text: str) -> None:
        if not self.__value.endswith(text):
            self.__add(text)

    def __get_base(self, level: int) -> str:
        if self.style & REQUIRES_FAKE_SPACES:
            return f"{self.__prefix}{level * BLANK_CHAR * 2}"
        return f"{self.__prefix}{level * "    "}"

    def __add_formatted(self, string: str, line: bool, level: int) -> None:
        if not line:
            self.__add(self.__get_base(level))

        self.__add(string)

        if not line and self.style == Style.TXT:
            self.__add('\n')

    def __add_children(self, e: Tag | NavigableString, line: bool = False, level: int = 0) -> None:
        if isinstance(e, NavigableString):
            if e.strip() == "":
                return

            if self.__value.endswith('\n'):
                self.__add(self.__prefix)

            pref: str = ' ' if not self.empty() and self.__value[-1] not in [' ', BLANK_CHAR] else ''
            text: str = re.sub(r"^[ \n]+", pref, e.string)
            text      = text.replace('\n', ' ')
            self.__add(re.sub(r"  +", ' ', text))
            return

        for child in e.contents:
            self.add(child, line, level)

    def __add_generic_header(self, e: Tag, make_header: Callable[[str], str]) -> None:
        if e.find('a'):
            self.__add_a(e.find('a'), line=True)

        text: str = e.get_text(strip=True).replace('\n', ' ')
        self.__add(f"{make_header(text)}" +
                   f"{self.__prefix}\n")

    def __add_a(self, e: Tag, line: bool = False, level: int = 0) -> None:
        if not line:
            self.__add(self.__get_base(level))

        repl: str = self.style.make_break() if not line else ''
        text: str = e.get_text(strip=True).replace('\n', repl)
        if e.has_attr("href") and self.style not in [Style.RS, Style.TXT]:
            content: str = e["href"].strip()
            if content.startswith("http"):   # Direct link
                link: str = content
            elif content.startswith('#'):    # Relative link
                link: str = f"{self.url}{content}"
            elif content.endswith(".html"):  # Relative file link
                link: str = f"{VULKAN_REGISTRY}{content}"
            else:
                return

            self.__add(self.style.make_ref(text, link))
        else:
            # Anchor without link should be treated as text
            self.__add(text)

        if not line and self.style == Style.TXT:
            self.__add('\n')

    def __add_br(self, _1: Tag = None, _2: bool = False, level: int = 0) -> None:
        self.__add(self.style.make_break())
        self.__add(self.__get_base(level))

    def __add_code(self, e: Tag, line: bool = False, level: int = 0) -> None:
        text: str = e.get_text(strip=True).replace('\n', '')
        self.__add_formatted(self.style.make_bold(text), line, level)

    def __add_dt(self, e: Tag, _1: bool = False, level: int = 0) -> None:
        text: str = e.get_text(strip=True)
        if text.strip() == "":
            return

        self.__add(self.__prefix + self.style.make_dt(text, self.__prefix, level))

    def __add_em(self, e: Tag, line: bool = False, level: int = 0) -> None:
        text: str = e.get_text(strip=True).replace('\n', '')
        self.__add_formatted(self.style.make_italic(text), line, level)

    def __add_h2(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        if not self.empty():
            if self.style.has_html_lists():
                # Add a <br> after lists if before a title
                start: int = len("</ul>\n * \n") + self.indentation_level * 4
                end: int   = start + len("</ul>")

                if self.__value[-start:-end] == "</ul>" or self.__value[-start:-end] == "</dl>":
                    self.__value = self.__value[:-9] + f"<br>\n{self.__prefix}\n{self.__prefix}"
            elif not self.__value.endswith("* \n") and not self.__value.endswith("**\n"):
                # If there is not an empty line add one
                self.__add(f"{self.__prefix}\n")

        self.__add(self.__prefix)
        self.__add_generic_header(e, self.style.make_header2)

    def __add_h3(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        self.__add(self.__prefix)
        self.__add_generic_header(e, self.style.make_header3)

    def __add_li(self, e: Tag, _1: bool = False, level: int = 0) -> None:
        self.__add(self.__prefix)
        self.__add(self.style.make_list_entry(e.name, level))
        self.__add_children(e, True, level + 1)
        self.__suffix('\n')

    def __add_listingblock(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        text: str = e.find("pre").get_text(strip=True)

        if self.style == Style.RS:
            self.__value = self.__value.removesuffix(self.__prefix + '\n')
            self.__value = self.__value.removesuffix("<br>\n")
            self.__suffix('\n')

        self.__add(self.style.make_codeblock(self.__prefix, self.__indentation_level, text))

    def __optional_add_p(self, e: Tag, line: bool = False, level: int = 0) -> None:
        self.__add_children(e, line, level)
        self.__suffix('\n')

    def __add_paragraph(self, e: Tag, line: bool = False, level: int = 0) -> None:
        # Some styles require a safety check to ensure that
        # the paragraph has something at its left
        if not line or self.__value.endswith('\n'):
            self.__add(self.__get_base(level))

        self.__add_children(e, line=True)

        match self.style:
            case Style.CL:
                self.__add("<br><br>")
            case Style.RS:
                self.__add("<br>")

        if not line:
            self.__add(f"\n{self.__prefix}\n")

    def __add_sidebarblock(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        self.__add_children(e.find('div', class_="content"))

    def __add_span(self, e: Tag, line: bool = False, level: int = 0) -> None:
        text: str = e.get_text(strip=True)
        if e.get('class') and e.get('class') == ['eq']:
            # eq class span are math expressions
            tmp = DocumentationBlock(self.url, self.style, self.indentation_level)
            tmp.__add_children(e, line=True)
            text = tmp.__value

        if text.strip() == "":
            return

        if line:
            self.__add(f"{text.replace('\n', ' ')}")
            return

        self.__add(self.__get_base(level) + f"{text.replace('\n', ' ')}")

    def __add_strong(self, e: Tag, line: bool = False, level: int = 0) -> None:
        # Sometimes there is not a space between text and a <strong>
        if not self.empty():
            self.__suffix(' ')

        text: str = e.get_text(strip=True).replace('\n', ' ')
        self.__add_formatted(self.style.make_bold_italic(text), line, level)

    def __add_sub(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        tmp = DocumentationBlock(self.url, self.style, self.indentation_level)
        tmp.__add_children(e, line=True)
        self.__add(self.style.make_sub(tmp.__value))

    def __add_table(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        def fix_html(item: Tag) -> str:
            for br in item.find_all("br"):
                br.replace_with(NavigableString('\n'))

            text: str = ''.join(str(content) for content in item.contents)

            # Remove html, extra '\n' and ' '
            text = re.sub(r"\s*\n\s*", '\n', text.strip())
            text = re.sub(r"<[^<>]+>", '', text)
            text = re.sub(r" +", ' ', text)

            return html.unescape(text)

        trs: list    = e.find_all("tr")
        rows: list   = []  # A row is a list of cells (list[str])
        columns: int = 0

        for tr in trs:
            row: list = []
            for cell in tr.find_all(["th", "td"]):
                text: str = fix_html(cell)
                colspan   = int(cell.get("colspan", 1))

                row.append(text)
                for _ in range(colspan - 1):
                    row.append(None)

            columns = max(columns, len(row))
            rows.append(row)

        for row in rows:
            row.extend([''] * (columns - len(row)))

        widths: list = [max(len(line) for cell in col if cell is not None for line in str(cell).split("\n")) + 2 for col in zip(*rows)]
        self.__add(self.style.make_table(self.__prefix, rows, widths, columns))

    def __add_ul(self, e: Tag, line: bool = False, level: int = 0) -> None:
        type: str = f"{e.name[0]}l"

        if line:
            self.__add('\n')

        if not self.style.has_html_lists():
            self.__add_children(e, level=level)
            self.__suffix(f"\n{self.__prefix}\n")
            return

        self.__add(f"{self.__prefix}{level * "    "}<{type}>\n")
        self.__add_children(e, level=level + 1)
        self.__add(f"{self.__prefix}{level * "    "}</{type}>")

        if not line:
            self.__add(f"\n{self.__prefix}\n")


class Clock:
    def __init__(self, action: str) -> None:
        self.__action: str  = action
        self.__start: float = time()

    def __enter__(self) -> "Clock":
        return self

    def __exit__(self, exc_type, exc_val, exc_tb) -> None:
        if exc_type is None:
            print(f"{self.__action} completed in {time() - self.__start}s.")


def _pool_executor_helper(args: tuple) -> Any:
    return args[0](*args[1:])


class PoolExecutor(ProcessPoolExecutor):
    def __init__(self, func: Callable):
        super().__init__()
        self.__func = func

    def exec(self, iterables: Iterable, timeout=None, chunksize=1) -> Any:
        args = list(map(lambda item: (self.__func, *item), iterables))
        return super().map(_pool_executor_helper, args, timeout=timeout, chunksize=chunksize)


def parse_args() -> tuple[str, Style, bool, bool, str | None]:
    def get_version() -> str:
        request: Response = requests.get(VULKAN_VALID_USAGE)
        data: dict        = request.json()
        version: str      = data["version info"]["api version"]
        return 'v' + version

    parser = ArgumentParser(
        prog="Vulkan Documented Headers Generator",
        description="Generate the Vulkan headers with code documentation")
    parser.add_argument(
        "output_path",
        help="Where the vulkan/ directory will be generated")
    parser.add_argument(
        "-V", "--version",
        help="Vulkan headers version to clone and edit, latest available if not " +
             "provided. Example: v1.2.131")
    parser.add_argument(
        "-S", "--style",
        choices=["TXT", "CL", "RS", "VSC"],
        default="TXT",
        help="Documentation style, plain text or IDE/Editor specific")
    parser.add_argument(
        "-N", "--namespace",
        action="store_true",
        default=False,
        help="Put a alias in the vk:: namespace")
    parser.add_argument(
        "-F", "--force",
        action="store_true",
        default=False,
        help="Force the generation even if the version matches the current one")

    args = parser.parse_args()
    if not args.version:
        args.version = get_version()

    return args.output_path, Style[args.style], args.namespace, args.force, args.version


def should_regenerate(output_path: str, style: Style, namespace: bool, version: str) -> tuple[bool, str]:
    current: str = f"{version} {style} {namespace}"

    if path.exists(VERSION_FILE) and path.exists(output_path):
        with open(VERSION_FILE, 'r', encoding="utf-8") as f:
            data: str = f.read()

        if data == current:
            print(f"Current headers match the most recent version of "
                  f"Vulkan ({version}) and use the correct flags. Not "
                  f"generating.")
            return False, current

        old_version = data.split(' ')[0]
        if old_version == version:
            print(f"Current headers match the most recent version of "
                  f"Vulkan ({version}), but use the wrong flags.")
        else:
            print(f"Current headers (v {old_version}) do not match the "
                  f"most recent version of Vulkan ({version}).")

        os.remove(VERSION_FILE)

    return True, current


def onerror(func, path: str, _) -> None:
    if not os.access(path, os.W_OK):
        os.chmod(path, stat.S_IWUSR)
        func(path)
    else:
        raise PermissionError("Could not delete cloned directory.")


def prepare_environment(output: str) -> None:
    if path.exists(output):
        shutil.rmtree(output, onexc=onerror)

    os.mkdir(output)
    os.mkdir(path.join(output, "vulkan"))

    src: str = path.join(HEADERS_REPO_PATH, "include", "vk_video")
    dst: str = path.join(output, "vk_video")
    if path.exists(src):  # Old vulkan versions don't have vk_video
        os.rename(src, dst)


def get_element_documentation(name: str, style: Style, namespace: bool) -> tuple[str, str]:
    def get_html(name: str) -> str:
        registry: str = f"{REGISTRY_REPO_PATH}/specs/latest/man/html/{name}.html"
        if not path.exists(registry):
            raise FileNotFoundError(registry)

        with open(registry, 'r', encoding="utf-8") as f:
            data: str = f.read()

            if len(data) > 256:
                return data

            redirect: str = f"{REGISTRY_REPO_PATH}/specs/latest/man/html/{data}"
            if path.exists(redirect):
                return open(redirect, 'r', encoding="utf-8").read()

            return data

    indent: int = 1 if namespace else 0
    soup        = BeautifulSoup(get_html(name), "html.parser")

    start: Tag     = soup.find("h1")
    content: Tag   = soup.find("div", id="content")
    header: Tag    = start.find_next("h2")
    paragraph: Tag = start.find_next("div", class_="sectionbody")

    if not all([content, header, paragraph]):
        return name, ""

    documentation = DocumentationBlock(name, style, indent)
    documentation.add(header)
    documentation.add(paragraph, name="paragraph")

    def should_print(e: Tag) -> bool:
        return e.find('h2').get_text(strip=True) not in NOT_PRINTED_DIVS

    for section in filter(should_print, content.find_all('div', class_="sect1")):
        documentation.add(section)

    # The name is returned to easily construct a dictionary later
    return name, documentation.value


def generate_documentations(style: Style, namespace: bool) -> dict[str, str]:
    base: str = f"{REGISTRY_REPO_PATH}/specs/latest/man/html/"

    def make_arg(path: str) -> tuple[str, Style, bool]:
        return Path(path).stem, style, namespace

    def can_generate(name: str) -> bool:
        return name.startswith("Vk") or name.startswith("vk") or name.startswith("VK_")

    args = filter(can_generate, os.listdir(base))
    args = map(make_arg, args)
    with PoolExecutor(get_element_documentation) as executor:
        docs = dict(executor.exec(args))

    return docs


def write_file_documentation(output: str, input: str, docs: dict[str, str], style: Style, namespace: bool) -> None:
    # TODO: this function sucks rewrite it
    def add_documentation(match: Match[str], name: str, function: bool = False, macro: bool = False) -> str:
        def camel_case(string: str) -> str:
            return string[0].lower() + string[1:]

        if name not in docs:
            return match.group(0)

        if not namespace or macro:
            return docs[name] + match.group(0)

        text: str = f"auto constexpr {camel_case(name[2:])}" if function else f"using {name[2:]}"
        return match.group(0) + "namespace vk {\n" +        \
                               f"{docs[name]}" +            \
                               f"    {text} = {name};\n" +  \
                                "}\n"

    with open(input, 'r', encoding="utf-8") as f:
        data: str = f.read()

    data = re.sub(COMMENT_REGEX, '', data)

    # TODO fix macros in TXT mode.
    if style != Style.TXT:
        data = re.sub(DEFINITION_REGEX, lambda match: add_documentation(match, match.group(1), macro=True), data)

    data = re.sub(HANDLE_REGEX,   lambda match: add_documentation(match, match.group(3) or match.group(5)), data)
    data = re.sub(FUNCTION_REGEX, lambda match: add_documentation(match, match.group(2), function=True), data)
    data = re.sub(TYPEDEF_REGEX,  lambda match: add_documentation(match, match.group(2)), data)
    data = re.sub(r"\n\n+", "\n\n", data)

    with open(input, 'w', encoding="utf-8") as f:
        f.write(data)

    output = path.join(output, "vulkan", path.basename(input))
    os.rename(input, output)


def write_documentation(output: str, docs: dict[str, str], style: Style, namespace: bool) -> None:
    base: str = f"{HEADERS_REPO_PATH}/include/vulkan"

    def make_arg(path: str) -> tuple[str, str, dict, Style, bool]:
        return output, f"{base}/{path}", docs, style, namespace

    def is_header(name: str) -> bool:
        return name.endswith(".h")

    args = filter(is_header, os.listdir(base))
    args = map(make_arg, args)
    with PoolExecutor(write_file_documentation) as executor:
        executor.exec(args)


def main() -> None:
    def clone(url: str, out: str, version: str | None = None) -> None:
        branch: str = version if version else "main"
        try:
            subprocess.run(["git", "clone", url, "--branch", branch, *CLONE_ARGS, out], check=True)
        except Exception as e:
            print(f"Failed to clone repository '{url}' branch '{branch}'.")
            raise e

    if sys.version_info < (3, 12):
        raise EnvironmentError("Script requires Python 3.12 or newer.")

    output_path, style, namespace, force, version = parse_args()
    if force and path.exists(VERSION_FILE):
        os.remove(VERSION_FILE)

    regen, output = should_regenerate(output_path, style, namespace, version)
    if not regen:
        return

    print("Downloading headers and registry...")
    with Clock("Downloads"):
        clone("https://github.com/KhronosGroup/Vulkan-Headers.git", HEADERS_REPO_PATH, version)
        clone("https://github.com/KhronosGroup/Vulkan-Registry.git", REGISTRY_REPO_PATH)

    try:
        prepare_environment(output_path)

        print("Generating the documentation and headers...")
        with Clock("Documentation generation"):
            docs: dict = generate_documentations(style, namespace)
            write_documentation(output_path, docs, style, namespace)
    except Exception as e:
        print("An error occurred. Deleting malformed output...")
        shutil.rmtree(output_path, onexc=onerror)
        raise e
    finally:
        print("Clearing downloaded content...")
        shutil.rmtree(HEADERS_REPO_PATH,  onexc=onerror)
        shutil.rmtree(REGISTRY_REPO_PATH, onexc=onerror)

    with open(VERSION_FILE, 'w', encoding="utf-8") as f:
        f.write(output)


if __name__ == "__main__":
    main()

# TODO fix images https://registry.khronos.org/vulkan/specs/latest/man/html/VkPrimitiveTopology.html
