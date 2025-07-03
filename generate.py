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
from enum import Enum
from pathlib import Path
from requests import Response
from typing import Final, Callable
from bs4 import BeautifulSoup, Tag
from argparse import ArgumentParser
from concurrent.futures import ProcessPoolExecutor
from bs4.element import NavigableString, PageElement, AttributeValueList


# Constants
VULKAN_VALID_USAGE: Final = "https://raw.githubusercontent.com/KhronosGroup/Vulkan-Registry/refs/heads/main/specs/latest/validation/validusage.json"
VULKAN_REGISTRY: Final    = "https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/"
VERSION_FILE: Final       = "./.version.txt"
NOT_PRINTED_DIVS: Final   = ["Document Notes", "See Also", "Copyright"]
CLONE_ARGS: Final         = ["--branch", "main", "--single-branch", "--depth", "1", "--quiet"]
THREADS: Final            = os.cpu_count()
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


class Style(Enum):
    TXT = -1  # Plain text
    CL  =  0  # CLion
    RS  =  1  # ReSharper
    VSC =  2  # Visual Studio Code

    def make_bold(self, text: str) -> str:
        if self in [Style.CL, Style.RS]:
            return f"<b>{text}</b>"
        return text

    def make_italic(self, text: str) -> str:
        if self in [Style.CL, Style.RS]:
            return f"<i>{text}</i>"
        return text

    def make_bold_italic(self, text: str) -> str:
        if self in [Style.CL]:
            return f"<b><i>{text}</i></b>"
        if self in [Style.RS]:
            return f"<b>{text}</b>"
        return text

    def make_sub(self, text: str) -> str:
        if self in [Style.CL, Style.RS]:
            return f"<sub>{text}</sub>"
        return text

    def make_ref(self, text: str, url: str) -> str:
        if self in [Style.CL]:
            return f"<a href=\"{url}\">{text}</a>"

        text = text if text != "" else "↖ "
        return f"[{text}]({url})"

    def make_header(self, text: str) -> str:
        if self in [Style.CL, Style.RS]:
            return f"<b>{text}</b><hr>"
        return text


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

        # Extra CLion specific fixes
        if self.style == Style.CL:
            # Remove space after list entry begin
            string = string.replace("<li> ", "<li>")

            # Merge adjacent lists
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

    @value.setter
    def value(self, value: object) -> None:
        raise AttributeError("You can not assign a value to 'value' directly.")

    @property
    def url(self) -> str:
        return self.__url

    @url.setter
    def url(self, value: object) -> None:
        raise AttributeError("You can not assign a new value to url after initialization.")

    @property
    def style(self) -> Style:
        return self.__style

    @style.setter
    def style(self, value: object) -> None:
        raise AttributeError("You can not assign a new value to style after initialization.")

    @property
    def indentation_level(self) -> int:
        return self.__indentation_level

    @indentation_level.setter
    def indentation_level(self, value: object) -> None:
        raise AttributeError("You can not assign a new value to indentation_level " +
                             "after initialization.")

    def __get_base(self, level: int) -> str:
        match self.style:
            case Style.CL:
                return f"{self.__prefix}{level * "    "}"
            case Style.RS:
                return f"{self.__prefix}{level * "  "}"
            case _:
                return f"{self.__prefix}{level * BLANK_CHAR * 2}"

    def __add_formatted(self, string: str, line: bool, level: int) -> None:
        if not line:
            self.__value += self.__get_base(level)

        self.__value += string

        if not line and self.style == Style.TXT:
            self.__value += '\n'

    def __add_children(self, e: Tag | NavigableString, line: bool = False, level: int = 0) -> None:
        if isinstance(e, NavigableString):
            if e.strip() == "":
                return

            pref: str = ' ' if not self.empty() and self.__value[-1] not in [' ', BLANK_CHAR] else ''
            text: str = re.sub(r"^[ \n]+", pref, e.string)
            text      = text.replace('\n', ' ')
            self.__value += re.sub(r"  +", ' ', text)
            return

        # If not we cycle through all of its children
        for child in e.contents:
            self.add(child, line, level)

    def __add_a(self, e: Tag, line: bool = False, level: int = 0) -> None:
        if not line:
            self.__value += self.__get_base(level)

        repl: str = f"{"<br>\n" if self.style == Style.CL else '\n'}" if not line else ''
        text: str = e.get_text(strip=True).replace('\n', repl)
        if e.has_attr("href") and self.style not in [Style.RS, Style.TXT]:
            content: str = e["href"].strip()
            if content.startswith("http"):  # Direct link
                link: str = content
            elif content.startswith('#'):  # Relative link
                link: str = f"{self.url}{content}"
            elif content.endswith(".html"):  # Relative file link
                link: str = f"{VULKAN_REGISTRY}{content}"
            else:
                return

            self.__value += self.style.make_ref(text, link)
        else:
            # Anchor without link should be treated as text
            self.__value += text

        if not line and self.style == Style.TXT:
            self.__value += '\n'

    def __add_br(self, _1: Tag = None, _2: bool = False, level: int = 0) -> None:
        if self.style == Style.CL:
            self.__value += "<br>"

        self.__value += "\n" + self.__get_base(level)

    def __add_code(self, e: Tag, line: bool = False, level: int = 0) -> None:
        text: str = e.get_text(strip=True).replace('\n', '')
        self.__add_formatted(self.style.make_bold(text), line, level)

    def __add_dt(self, e: Tag, _1: bool = False, level: int = 0) -> None:
        text: str = e.get_text(strip=True)
        if text.strip() == "":
            return

        if self.style == Style.CL:
            self.__value += f"{self.__prefix}{level * "    "}<dt><b>{text}</b>\n"
            return

        if self.__value[-3:] != "* \n":
            self.__value += f"{self.__prefix}\n"

        if self.style in [Style.RS, Style.TXT]:
            self.__value += f"{self.__prefix}{level * "  "}{text}\n"
        else:
            self.__value += f"{self.__prefix}{level * BLANK_CHAR * 2}#### {BLANK_CHAR}{text}\n" + \
                            f"{self.__prefix}\n"

    def __add_em(self, e: Tag, line: bool = False, level: int = 0) -> None:
        text: str = e.get_text(strip=True).replace('\n', '')
        self.__add_formatted(self.style.make_italic(text), line, level)

    def __add_h2(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        if not self.empty():
            if self.style == Style.CL:
                # Add a <br> after lists if before a title
                start: int = len("</ul>\n * \n") + self.indentation_level * 4
                end: int   = start + len("</ul>")

                if self.__value[-start:-end] == "</ul>" or self.__value[-start:-end] == "</dl>":
                    self.__value = self.__value[:-9] + f"<br>\n{self.__prefix}\n{self.__prefix}"
            elif self.__value[-3:] != "* \n" and self.__value[-3:] != "**\n":
                # If there is not an empty line add one
                self.__value += f"{self.__prefix}\n"

        self.__value += self.__prefix
        if self.style == Style.VSC:
            self.__value += "## "

        if e.find('a'):
            self.__add_a(e.find('a'), line=True)

        text: str = e.get_text(strip=True).replace('\n', ' ')
        self.__value += f"{self.style.make_header(text)}\n" +   \
                        f"{self.__prefix}\n"

    def __add_h3(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        self.__value += self.__prefix
        if self.style == Style.VSC:
            self.__value += "### "

        if e.find('a'):
            self.__add_a(e.find('a'), line=True)

        text: str = e.get_text(strip=True).replace('\n', ' ')
        self.__value += f"{self.style.make_header(text)}\n" +   \
                        f"{self.__prefix}\n"

    def __add_li(self, e: Tag, _1: bool = False, level: int = 0) -> None:
        self.__value += self.__prefix
        match self.style:
            case Style.CL:
                self.__value += f"{level * "    "}<{e.name}>"
            case Style.RS:
                self.__value += f"{level * "  "}- "
            case _:
                self.__value += f"- {level * BLANK_CHAR * 4}"

        self.__add_children(e, True, level + 1)

        if self.__value[-1] != '\n':
            # If the last element added by 'addSubElements' didn't add a
            # return, add it here
            self.__value += '\n'

    def __add_listingblock(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        text: str = e.find("pre").get_text(strip=True)

        match self.style:
            case Style.CL | Style.RS:
                self.__value += f"{self.__prefix}@code\n"
                self.__value += f"{self.__prefix}{text.replace('\n', f"\n{self.__prefix}")}\n"
                self.__value += f"{self.__prefix}@endcode\n{self.__prefix}\n"
            case Style.VSC:
                spaces: str = self.indentation_level * "    "
                self.__value += f"```cpp\n"
                self.__value += f"{spaces}{text.replace('\n', f"\n{spaces}")}\n"
                self.__value += f"```\n{self.__prefix}\n"
            case _:
                self.__value += f"{self.__prefix}\n"
                self.__value += f"{self.__prefix}{text.replace('\n', f"\n{self.__prefix}")}\n"
                self.__value += f"{self.__prefix}\n"

    def __optional_add_p(self, e: Tag, line: bool = False, level: int = 0) -> None:
        self.__add_children(e, line, level)
        if self.__value[-1] != '\n':
            self.__value += '\n'

    def __add_paragraph(self, e: Tag, line: bool = False, level: int = 0) -> None:
        # Some styles require a safety check to ensure that
        # the paragraph has something at its left
        if not line or self.__value[-1] == '\n':
            self.__value += self.__get_base(level)

        self.__add_children(e, line=True)

        match self.style:
            case Style.CL:
                self.__value += "<br><br>"
            case Style.RS:
                self.__value += "<br>"

        if not line:
            self.__value += f"\n{self.__prefix}\n"

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
            self.__value += f"{text.replace('\n', ' ')}"
            return

        self.__value += self.__get_base(level) + f"{text.replace('\n', ' ')}"

    def __add_strong(self, e: Tag, line: bool = False, level: int = 0) -> None:
        # Sometimes there is not a space between text and a <strong>
        if not self.empty() and self.__value[-1] != ' ':
            self.__value += ' '

        text: str = e.get_text(strip=True).replace('\n', ' ')
        self.__add_formatted(self.style.make_bold_italic(text), line, level)

    def __add_sub(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        tmp = DocumentationBlock(self.url, self.style, self.indentation_level)
        tmp.__add_children(e, line=True)
        self.__value += self.style.make_sub(tmp.__value)

    def __add_table(self, e: Tag, _1: bool = False, _2: int = 0) -> None:
        def fix_html(item: Tag) -> str:
            for br in item.find_all("br"):
                br.replace_with('\n')

            text: str = ''.join(str(content) for content in item.contents)

            # Remove html, extra '\n' and ' '
            text = re.sub(r"\s*\n\s*", '\n', text.strip())
            text = re.sub(r"<[^<>]+>", '', text)
            text = re.sub(r" +", ' ', text)

            return html.unescape(text)

        def format_line(lines: list[list[str]], line_idx: int) -> str:
            if self.style in [Style.CL, Style.TXT]:
                line: str = f"{self.__prefix}|  "

                for cell_idx, cell_lines in enumerate(lines):
                    text: str = (cell_lines[line_idx] if cell_lines[line_idx] is not None else '') if line_idx < len(cell_lines) else ''
                    sep: str  = '|' if not cell_idx < len(lines) - 1 or (line_idx < len(lines[cell_idx + 1]) and lines[cell_idx + 1][line_idx] is not None) else ' '
                    line     += f"{text:<{widths[cell_idx] - 2}}  {sep}  "

                if self.style == Style.TXT:
                    line = line.replace(' ', BLANK_CHAR)

                return line[:-2] + term
            else:
                line: str = f"{self.__prefix}|{FAKE_PIPE_CHAR} "

                for cell_idx, cell_lines in enumerate(lines):
                    text: str = (cell_lines[line_idx] if cell_lines[line_idx] is not None else '') if line_idx < len(cell_lines) else ''
                    sep: str  = FAKE_PIPE_CHAR if not cell_idx < len(lines) - 1 or (line_idx < len(lines[cell_idx + 1]) and lines[cell_idx + 1][line_idx] is not None) else ''
                    line     += f"{text} |{sep} "

                return line + '|'

        def format_row(row: list[str | None]) -> list[str]:
            # lines[cellIdx][lineIdx], contains all the lines for each cell.
            lines: list = [str(cell).split("\n") if cell is not None else [None] for cell in row]
            indexes     = range(max(len(cellLines) for cellLines in lines))

            return [format_line(lines, idx) for idx in indexes]

        if self.style not in [Style.CL, Style.VSC, Style.TXT]:
            return

        term: str    = '' if self.style == Style.TXT else "<br>"
        trs: list    = e.find_all("tr")
        rows: list   = []  # A row is a list of cells (list[str])
        columns: int = 0

        for tr in trs:
            row: list = []
            for cell in tr.find_all(["th", "td"]):
                text    = fix_html(cell)
                colspan = int(cell.get("colspan", 1))

                row.append(text)
                for _ in range(colspan - 1):
                    row.append(None)

            columns = max(columns, len(row))
            rows.append(row)

        for row in rows:
            while len(row) < columns:
                row.append('')

        widths: list = [max(len(line) for cell in col if cell is not None for line in str(cell).split("\n")) + 2 for col in zip(*rows)]

        if self.style in [Style.CL, Style.TXT]:
            line: str   = self.__prefix + '-' * (sum(widths) + 3 * len(widths) + 1) + term
            table: list = [line]
        else:
            line: str   = self.__prefix + "| :-- " * (columns + 1) + '|'
            table: list = [*format_row(rows[0]), line]

        for row in rows[(0 if self.style in [Style.CL, Style.TXT] else 1):]:
            table.extend(format_row(row))
            if self.style in [Style.CL, Style.TXT]:
                table.append(line)

        # Saves the table
        if self.style == Style.CL:
            self.__value += f"{self.__prefix}<pre>\n"

        self.__value += '\n'.join(table) + '\n'

        if self.style == Style.CL:
            self.__value += f"{self.__prefix}</pre><br>\n{self.__prefix}\n"

    def __add_ul(self, e: Tag, line: bool = False, level: int = 0) -> None:
        type: str = f"{e.name[0]}l"

        if line:
            self.__value += '\n'

        if self.style == Style.CL:
            self.__value += f"{self.__prefix}{level * "    "}<{type}>\n"
            self.__add_children(e, level=level + 1)
        else:
            self.__add_children(e, level=level)
            return

        self.__value += f"{self.__prefix}{level * "    "}</{type}>"

        if line:
            return

        self.__value += f"\n{self.__prefix}\n"


def parse_args() -> tuple[str, Style, bool, bool]:
    assert sys.version_info >= (3, 12), "Script requires Python 3.12 or newer."

    parser = ArgumentParser(
        prog="Vulkan Documented Headers Generator",
        description="Generate the Vulkan headers with code documentation")

    parser.add_argument(
        "output_path",
        help="Where the vulkan/ directory will be generated")
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
    return args.output_path, Style[args.style], args.namespace, args.force


def should_regenerate(output_path: str, style: Style, namespace: bool) -> tuple[bool, str]:
    def get_version() -> str:
        request: Response = requests.get(VULKAN_VALID_USAGE)
        data: dict = request.json()
        version: str = data["version info"]["api version"]

        return version

    version: str = get_version()
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
    os.rename(src, dst)


def get_element_documentation(args: tuple[str, Style, bool]) -> tuple[str, str]:
    name, style, namespace = args

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
    with ProcessPoolExecutor() as executor:
        docs = dict(executor.map(get_element_documentation, args))

    return docs


def write_file_documentation(args: tuple[str, str, dict[str, str], Style, bool]) -> None:
    output, input, docs, style, namespace = args

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

    data = re.sub(HANDLE_REGEX, lambda match: add_documentation(match, match.group(3) or match.group(5)), data)
    data = re.sub(FUNCTION_REGEX, lambda match: add_documentation(match, match.group(2), function=True), data)
    data = re.sub(TYPEDEF_REGEX, lambda match: add_documentation(match, match.group(2)), data)
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
    with ProcessPoolExecutor() as executor:
        executor.map(write_file_documentation, args)


def main() -> None:
    def clone(url: str, out: str) -> None:
        subprocess.run(["git", "clone", url, *CLONE_ARGS, out], check=True)

    start: float = time()

    output_path, style, namespace, force = parse_args()
    if force:
        os.remove(VERSION_FILE)

    regen, output = should_regenerate(output_path, style, namespace)
    if not regen:
        print(f"Action completed in {time() - start}s.")
        return

    print("Downloading headers and registry...")
    clone("https://github.com/KhronosGroup/Vulkan-Headers.git", HEADERS_REPO_PATH)
    clone("https://github.com/KhronosGroup/Vulkan-Registry.git", REGISTRY_REPO_PATH)

    try:
        print("Generating the documentation and headers...")
        prepare_environment(output_path)
        docs: dict = generate_documentations(style, namespace)

        print("Writing documentation...")
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

    print(f"Action completed in {time() - start}s.")


if __name__ == "__main__":
    main()

# TODO fix images https://registry.khronos.org/vulkan/specs/latest/man/html/VkPrimitiveTopology.html
