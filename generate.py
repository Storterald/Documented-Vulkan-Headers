import re
import os
import sys
import html
import stat
import shutil
import subprocess

from re import Match
from time import time
from enum import Enum
from typing import Final
from types import NoneType
from bs4 import BeautifulSoup, Tag
from concurrent.futures import ProcessPoolExecutor
from bs4.element import NavigableString, PageElement


class Style(Enum):
        TXT = -1  # Plain text
        CL  =  0  # CLion
        RS  =  1  # ReSharper
        VSC =  2  # Visual Studio Code


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


class DocumentationBlock:
        def __init__(self, name: str, style: Style, indentLevel: int) -> None:
                self.__value        = ""
                self.__STYLE        = style
                self.__URL          = f"{VULKAN_REGISTRY}{name}.html"
                self.__INDENT_LEVEL = indentLevel
                self.__PREFIX       = indentLevel * "    " + " * " if style != Style.TXT else ''

                # Function aliases
                self.__add_dd = self.__add_li if self.__STYLE == Style.CL else self.__add_children
                self.__add_sectionbody = self.__add_children
                self.__add_dl = self.__add_ul
                self.__add_title = self.__add_h2

                if style == Style.TXT:
                        self.__add_p = self.__optional_add_p;
        
        def add(self, e: PageElement, singleLine: bool = False, listLevel: int = 0, type: str | None = None):
                if isinstance(e, NavigableString):
                        self.__add_children(e, singleLine, listLevel)
                        return
                
                assert isinstance(e, Tag), "Invalid element type"
                
                def make_name(name: str) -> str:
                        return f"_{self.__class__.__name__}__add_{name}"
                
                if type:
                        function = getattr(self, make_name(type), None)
                        assert function, "Unsupported type passed to add."
                        return function(e, singleLine, listLevel)
                
                type = e.name if e.name != "div" else ' '.join(e.get('class', []))
                re.sub("[^a-zA-Z0-9_]", '_', type)
                
                function = getattr(self, make_name(type), None)
                if function:
                        function(e, singleLine, listLevel)
                else:
                        # If the type is unknown, add the element children
                        self.__add_children(e, singleLine, listLevel)
        
        def __add_a(self, e: Tag, singleLine: bool = False, listLevel: int = 0) -> None:
                if not singleLine:
                        self.__value += self.__get_base(listLevel)
                
                repl: str = f"{"<br>\n" if self.__STYLE == Style.CL else '\n'}" if not singleLine else ''
                text: str = e.get_text(strip=True).replace('\n', repl)
                if e.has_attr("href") and self.__STYLE not in [Style.RS, Style.TXT]:
                        content: str = e["href"].strip()
                        if content.startswith("http"):
                                # Direct link
                                link: str = content
                        elif content.startswith('#'):
                                # Relative link
                                link: str = f"{self.__URL}{content}"
                        elif content.endswith(".html"):
                                # Relative file link
                                link: str = f"{VULKAN_REGISTRY}{content}"
                        else:
                                return
                        
                        if self.__STYLE == Style.CL:
                                # CLion already renders an arrow for hrefs.
                                self.__value += f"<a href=\"{link}\">{text}</a>"
                        else:
                                text = text if text != "" else "↖ "
                                self.__value += f"[{text}]({link})"
                else:
                        # Anchor without link should be printed as text
                        self.__value += text
                
                if not singleLine and self.__STYLE == Style.TXT:
                        self.__value += '\n'
        
        def __add_br(self, _unused1: NoneType = None, _unused2: NoneType = None, listLevel: int = 0) -> None:
                if self.__STYLE == Style.CL:
                        # Only CLion requires a break the <br> element
                        self.__value += "<br>"
                
                self.__value += "\n" + self.__get_base(listLevel)
        
        def __add_code(self, e: Tag, singleLine: bool = False, listLevel: int = 0) -> None:
                text: str = e.get_text(strip=True).replace('\n', '')

                if self.__STYLE in [Style.CL, Style.RS]:
                        self.__add_formatted(f"<b>{text}</b>", singleLine, listLevel)
                else:
                        # VS Code does not support markdown bold nor italic
                        self.__add_formatted(text, singleLine, listLevel)
        
        def __add_dt(self, e: Tag, _unused: NoneType = None, listLevel: int = 0) -> None:
                text: str = e.get_text(strip=True)
                if text.strip() == "":
                        return
                
                if self.__STYLE == Style.CL:
                        self.__value += f"{self.__PREFIX}{listLevel * "    "}<dt><b>{text}</b>\n"
                        return
                
                if self.__value[-3:] != "* \n":
                        self.__value += f"{self.__PREFIX}\n"
                
                if self.__STYLE in [Style.RS, Style.TXT]:
                        self.__value += f"{self.__PREFIX}{listLevel * "  "}{text}\n"
                else:
                        self.__value += f"{self.__PREFIX}{listLevel * BLANK_CHAR * 2}#### {BLANK_CHAR}{text}\n{self.__PREFIX}\n"
        
        def __add_em(self, e: Tag, singleLine: bool = False, listLevel: int = 0) -> None:
                text: str = e.get_text(strip=True).replace('\n', '')
                
                if self.__STYLE in [Style.CL, Style.RS]:
                        self.__add_formatted(f"<i>{text}</i>", singleLine, listLevel)
                else:
                        # VS Code does not support html nor markdown bold or italic
                        self.__add_formatted(text, singleLine, listLevel)
        
        def __add_h2(self, e: Tag, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                if self.__value != "":
                        if self.__STYLE == Style.CL:
                                # Add a <br> after lists if before a title
                                start: int = len("</ul>\n * \n") + self.__INDENT_LEVEL * 4
                                end: int = start + len("</ul>")

                                if self.__value[-start:-end] == "</ul>" or self.__value[-start:-end] == "</dl>":
                                        self.__value = self.__value[:-9] + f"<br>\n{self.__PREFIX}\n{self.__PREFIX}"
                        elif self.__value[-3:] != "* \n" and self.__value[-3:] != "**\n":
                                # If there is not an empty line add one
                                self.__value += f"{self.__PREFIX}\n"
                
                self.__value += self.__PREFIX
                if self.__STYLE == Style.VSC:
                        # To correctly render the header, the ## need to be before
                        # everything else
                        self.__value += "## "
                
                if e.find('a'):
                        self.__add_a(e.find('a'), True)
                
                text: str = e.get_text(strip=True).replace('\n', ' ')
                match self.__STYLE:
                        case Style.CL | Style.RS:
                                self.__value += f"<b>{text}</b><hr>"
                        case _:
                                self.__value += text
                
                self.__value += f"\n{self.__PREFIX}\n"
        
        def __add_h3(self, e: Tag, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                self.__value += self.__PREFIX
                if self.__STYLE == Style.VSC:
                        self.__value += "### "
                
                if e.find('a'):
                        self.__add_a(e.find('a'), True)
                
                text: str = e.get_text(strip=True).replace('\n', ' ')
                if self.__STYLE in [Style.CL, Style.RS]:
                        self.__value += f"<b>{text}</b><hr>"
                else:
                        self.__value += text
                
                self.__value += f"\n{self.__PREFIX}\n"
        
        def __add_li(self, e: Tag, _unused: NoneType = None, listLevel: int = 0) -> None:
                self.__value += self.__PREFIX
                match self.__STYLE:
                        case Style.CL:
                                self.__value += f"{listLevel * "    "}<{e.name}>"
                        case Style.RS:
                                self.__value += f"{listLevel * "  "}- "
                        case _:
                                self.__value += f"- {listLevel * BLANK_CHAR * 4}"
                
                self.__add_children(e, True, listLevel + 1)
                
                if self.__value[-1] != '\n':
                        # If the last element added by 'addSubElements' didn't add a
                        # return, add it here
                        self.__value += '\n'
        
        def __add_listingblock(self, e: Tag, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                text: str = e.find("pre").get_text(strip=True)

                match self.__STYLE:
                        case Style.CL | Style.RS:
                                self.__value += f"{self.__PREFIX}@code\n"
                                self.__value += f"{self.__PREFIX}{text.replace('\n', f"\n{self.__PREFIX}")}\n"
                                self.__value += f"{self.__PREFIX}@endcode\n{self.__PREFIX}\n"
                        case Style.VSC:
                                spaces: str = self.__INDENT_LEVEL * "    "
                                self.__value += f"```cpp\n"
                                self.__value += f"{spaces}{text.replace('\n', f"\n{spaces}")}\n"
                                self.__value += f"```\n{self.__PREFIX}\n"
                        case _:
                                self.__value += f"{self.__PREFIX}\n"
                                self.__value += f"{self.__PREFIX}{text.replace('\n', f"\n{self.__PREFIX}")}\n"
                                self.__value += f"{self.__PREFIX}\n"
        
        def __optional_add_p(self, e: Tag, singleLine: bool = False, listLevel: int = 0) -> None:
                self.__add_children(e, singleLine, listLevel)
                if self.__value[-1] != '\n':
                        self.__value += '\n'

        def __add_paragraph(self, e: Tag, singleLine: bool = False, listLevel: int = 0) -> None:
                # Some styles require a safety check to ensure that
                # the paragraph has something at its left
                if not singleLine or self.__value[-1] == '\n':
                        self.__value += self.__get_base(listLevel)
                
                self.__add_children(e, True)
                
                match self.__STYLE:
                        case Style.CL:
                                self.__value += "<br><br>"
                        case Style.RS:
                                self.__value += "<br>"
                
                if not singleLine:
                        self.__value += f"\n{self.__PREFIX}\n"
        
        def __add_sidebarblock(self, e: Tag, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                self.__add_children(e.find('div', 'content'))
        
        def __add_span(self, e: Tag, singleLine: bool = False, listLevel: int = 0) -> None:
                text: str = e.get_text(strip=True)
                if e.get('class') and e.get('class') == ['eq']:
                        # eq class span are math expressions
                        tmp = DocumentationBlock(self.__URL, self.__STYLE, self.__INDENT_LEVEL)
                        tmp.__add_children(e, True)
                        text = tmp.__value
                
                if text.strip() == "":
                        return
                
                if singleLine:
                        self.__value += f"{text.replace('\n', ' ')}"
                        return
                
                self.__value += self.__get_base(listLevel) + f"{text.replace('\n', ' ')}"
        
        def __add_strong(self, e: Tag, singleLine: bool = False, listLevel: int = 0) -> None:
                # Sometimes there is not a space between text and a <strong>
                if self.__value != "" and self.__value[-1] != ' ':
                        self.__value += ' '
                
                text: str = e.get_text(strip=True).replace('\n', ' ')
                match self.__STYLE:
                        case Style.CL:
                                self.__add_formatted(f"<i><b>{text}</b></i>", singleLine, listLevel)
                        case Style.RS:
                                # ReSharper breaks bold italic, so we only use bold
                                self.__add_formatted(f"<b>{text}</b>", singleLine, listLevel)
                        case _:
                                self.__add_formatted(text, singleLine, listLevel)
        
        def __add_sub(self, e: Tag, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                # Get all subtext
                tmp = DocumentationBlock(self.__URL, self.__STYLE, self.__INDENT_LEVEL)
                tmp.__add_children(e, True)
                
                if self.__STYLE in [Style.CL, Style.RS]:
                        self.__value += f"<sub>{tmp.__value}</sub>"
                else:
                        self.__value += tmp.__value
        
        def __add_table(self, e: Tag, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                if self.__STYLE in [Style.RS]:
                        return
                
                term: str = '\n' if self.__STYLE == Style.TXT else "<br>"

                # Removes whitespace and breaks, adds spaces when needed
                def fix_html(item: Tag) -> str:
                        for br in item.find_all("br"):
                                br.replace_with('\n')
                        
                        text: str = ''.join(str(content) for content in item.contents)
                        
                        # Remove html, extra '\n' and ' '
                        text = re.sub(r"\s*\n\s*", '\n', text.strip())
                        text = re.sub(r"<[^<>]+>", '', text)
                        text = re.sub(r" +", ' ', text)
                        
                        return html.unescape(text)
                
                trs: list          = e.find_all("tr")
                rows: list         = []  # A row is a list of cells (list[str])
                maxColumns: int    = 0
                
                for tr in trs:
                        row: list = []
                        for cell in tr.find_all(["th", "td"]):
                                text = fix_html(cell)
                                colspan = int(cell.get("colspan", 1))
                                
                                row.append(text)
                                for _ in range(colspan - 1):
                                        row.append(None)
                        
                        maxColumns = max(maxColumns, len(row))
                        rows.append(row)
                
                for row in rows:
                        while len(row) < maxColumns:
                                row.append('')
                
                widths: list = [max(len(line) for cell in col if cell is not None for line in str(cell).split("\n")) + 2 for col in zip(*rows)]

                def format_line(lines: list[list[str]], lineIdx: int) -> str:
                        if self.__STYLE in [ Style.CL, Style.TXT ]:
                                line: str = f"{self.__PREFIX}|  "
                                
                                for cellIdx, cellLines in enumerate(lines):
                                        text: str = (cellLines[lineIdx] if cellLines[lineIdx] is not None else '') if lineIdx < len(cellLines) else ''
                                        sep: str  = '|' if not cellIdx < len(lines) - 1 or (lineIdx < len(lines[cellIdx + 1]) and lines[cellIdx + 1][lineIdx] is not None) else ' '
                                        line += f"{text:<{widths[cellIdx] - 2}}  {sep}  "
                                
                                if self.__STYLE == Style.TXT:
                                        line = line.replace(' ', BLANK_CHAR)

                                return line[:-2] + term
                        else:
                                line: str = f"{self.__PREFIX}|{FAKE_PIPE_CHAR} "
                                
                                for cellIdx, cellLines in enumerate(lines):
                                        text: str = (cellLines[lineIdx] if cellLines[lineIdx] is not None else '') if lineIdx < len(cellLines) else ''
                                        sep: str  = FAKE_PIPE_CHAR if not cellIdx < len(lines) - 1 or (lineIdx < len(lines[cellIdx + 1]) and lines[cellIdx + 1][lineIdx] is not None) else ''
                                        line += f"{text} |{sep} "
                                
                                return line + '|'
                
                def format_row(row: list[str | None]) -> list[str]:
                        # lines[cellIdx][lineIdx], contains all the lines for each cell.
                        lines: list = [str(cell).split("\n") if cell is not None else [None] for cell in row]
                        lineIdxes: range = range(max(len(cellLines) for cellLines in lines))
                        
                        return [format_line(lines, lineIdx) for lineIdx in lineIdxes]
                
                if self.__STYLE in [ Style.CL, Style.TXT ]:
                        breakLine: str  = self.__PREFIX + '-' * (sum(widths) + 3 * len(widths) + 1) + term
                        tableRows: list = [breakLine]
                else:
                        formatLine: str = self.__PREFIX + "| :-- " * (maxColumns + 1) + '|'
                        tableRows: list = [*format_row(rows[0]), formatLine]
                
                for row in rows[(0 if self.__STYLE in [ Style.CL, Style.TXT ] else 1):]:
                        tableRows.extend(format_row(row))
                        if self.__STYLE in [ Style.CL, Style.TXT ]:
                                tableRows.append(breakLine)

                # Saves the table
                if self.__STYLE == Style.CL:
                        self.__value += f"{self.__PREFIX}<pre>\n"
                
                self.__value += '\n'.join(tableRows) + '\n'
                
                if self.__STYLE == Style.CL:
                        self.__value += f"{self.__PREFIX}</pre><br>\n{self.__PREFIX}\n"
                
        def __add_ul(self, e: Tag, singleLine: bool = False, listLevel: int = 0) -> None:
                type: str = f"{e.name[0]}l"
                
                if singleLine:
                        self.__value += '\n'
                
                if self.__STYLE == Style.CL:
                        self.__value += f"{self.__PREFIX}{listLevel * "    "}<{type}>\n"
                        self.__add_children(e, listLevel=listLevel + 1)
                else:
                        self.__add_children(e, listLevel=listLevel)
                        return
                
                self.__value += f"{self.__PREFIX}{listLevel * "    "}</{type}>"
                
                if singleLine:
                        return
                
                self.__value += f"\n{self.__PREFIX}\n"
        
        def __get_base(self, listLevel: int) -> str:
                match self.__STYLE:
                        case Style.CL:
                                return f"{self.__PREFIX}{listLevel * "    "}"
                        case Style.RS:
                                # ReSharper uses markdown lists
                                return f"{self.__PREFIX}{listLevel * "  "}"
                        case _:
                                # The empty chars are different
                                return f"{self.__PREFIX}{listLevel * BLANK_CHAR * 2}"
        
        def __add_formatted(self, string: str, singleLine: bool, listLevel: int) -> None:
                if not singleLine:
                        self.__value += self.__get_base(listLevel)
                
                self.__value += string
                
                if not singleLine and self.__STYLE == Style.TXT:
                        self.__value += '\n'
        
        def __add_children(self, e: Tag | NavigableString, singleLine: bool = False, listLevel: int = 0) -> None:
                # If an element only contains text
                if isinstance(e, NavigableString):
                        if e.strip() != "":
                                # Remove the whitespace at the begin of the string only
                                # if it's not already empty
                                PREF: str = ' ' if self.__value != "" and self.__value[-1] not in [' ', BLANK_CHAR] else ''
                                
                                text: str = re.sub(r"^[ \n]+", f"{PREF}", e)
                                
                                # Some text areas contain extra spaces, invisible in the website
                                text = text.replace('\n', ' ')
                                self.__value += re.sub(r"  +", ' ', text)
                        
                        return
                
                # If not we cycle through all of its children
                for child in e.contents:
                        self.add(child, singleLine, listLevel)
        
        @property
        def value(self) -> str:
                string: str         = self.__value
                spaceCount: int     = self.__INDENT_LEVEL * 4
                emptyLineRegex: str = rf" {{{spaceCount + 1}}}\* "
                
                # Fix invalid chars
                for old, new in CHAR_FIX_MAP.items():
                        string = string.replace(old, new)
                
                if self.__STYLE in [Style.CL, Style.RS]:
                        # Remove break before code block
                        string = re.sub(rf"(<br>)+(\n{emptyLineRegex}\n {{{spaceCount + 1}}}\* @code)", r"\2", string)
                        
                        # Fix sub-text
                        string = re.sub(r"(?<=[\s,.=])([a-zA-Z])_([a-zA-Z]+)(?=[\s,.=])", r"\1<sub>\2</sub>", string)
                else:
                        def sub_text(match: Match[str]) -> str:
                                return match.group(1).upper() + match.group(2)
                        
                        # Fix sub-text
                        string = re.sub(r"(?<=[\s,.=])([a-zA-Z])_([a-zA-Z]+)(?=[\s,.=])", sub_text, string)
                
                # Extra CLion specific fixes
                if self.__STYLE == Style.CL:
                        # Remove space after list entry begin
                        string = string.replace("<li> ", "<li>")
                        
                        # Merge adjacent lists
                        string = string.replace(f"{self.__PREFIX}</ul>\n{self.__PREFIX}\n{self.__PREFIX}<ul>\n", "")
                        string = string.replace(f"{self.__PREFIX}</dl>\n{self.__PREFIX}\n{self.__PREFIX}<dl>\n", "")
                
                # Remove extra whitespace
                string = re.sub(rf"{emptyLineRegex}\n( {{{spaceCount + 1}}}\* \n)", r"\1", string)
                string = re.sub(rf"(({emptyLineRegex})( {{4}})+)( +)?", r"\1", string)
                
                if self.__STYLE == Style.RS:
                        string = re.sub(r"(@endcode[ \n*]+)<br>", r"\1", string)
                
                if self.__STYLE == Style.TXT:
                        string = re.sub(rf"^ {{{spaceCount}}} \* ", '', string, flags=re.MULTILINE)
                
                # Some documentation blocks may contain comments inside the @code
                # blocks, this avoids closing the documentation early.
                string = string.replace("*/", f"*{FAKE_SLASH_CHAR}")
                string = string.replace("/*", f"{FAKE_SLASH_CHAR}*")
                
                prefix: str = f"{self.__INDENT_LEVEL * "    "}/**\n"
                suffix: str = f"{self.__INDENT_LEVEL * "    "}*/\n"
                
                # Documentation end
                if string[-3:] == "* \n":
                        string = string[:-2] + "/\n"
                else:
                        if string[-1] != '\n':
                                string += '\n'
                        string += suffix
                
                return prefix + string


def should_regenerate(outputPath: str) -> tuple[bool, str]:
        def get_version() -> str:
                import requests
                from requests import Response
                
                request: Response = requests.get(VULKAN_VALID_USAGE)
                data: dict = request.json()
                version: str = data["version info"]["api version"]
                
                return version
        
        version: str = get_version()
        current: str = f"{version} {style} {useNamespace}"
        
        if os.path.exists(VERSION_FILE) and os.path.exists(outputPath):
                with open(VERSION_FILE, 'r', encoding="utf-8") as f:
                        data: str = f.read()
                
                if data == current:
                        print(f"Current headers match the most recent version of "
                              f"Vulkan ({version}) and use the correct flags. Not "
                              f"generating.")
                        return False, current
                
                oldVersion = data.split(' ')[0]
                if oldVersion == version:
                        print(f"Current headers match the most recent version of "
                              f"Vulkan ({version}), but use the wrong flags.")
                else:
                        print(f"Current headers (v {oldVersion}) do not match the "
                              f"most recent version of Vulkan ({version}).")
                
                os.remove(VERSION_FILE)
                
        return True, current


def onerror(func, path: str, _) -> None:
        if not os.access(path, os.W_OK):
                # Change file permission
                os.chmod(path, stat.S_IWUSR)
                func(path)
        else:
                # If error is not due to permission issues, raise
                raise Exception("Could not delete cloned directory.")


def prepare_environment(outputPath: str) -> None:
        # If output path is a new directory
        if os.path.exists(outputPath):
                shutil.rmtree(outputPath, onexc=onerror)
        
        os.mkdir(outputPath)
        os.mkdir(outputPath + "/vulkan/")
        
        src: str = f"{HEADERS_REPO_PATH}/include/vk_video/"
        dst: str = f"{outputPath}/vk_video/"
        os.rename(src, dst)


def get_element_documentation(name: str, style: Style, useNamespace: bool) -> tuple[str, str]:
        def get_html(name: str) -> str:
                path: str = f"{REGISTRY_REPO_PATH}/specs/latest/man/html/{name}.html"
                assert os.path.exists(path), f"Could not find HTML file for '{name}'"
                
                with open(path, 'r', encoding="utf-8") as f:
                        data: str = f.read()
                        
                        # Some files may redirect to others
                        if len(data) > 256:
                                return data
                        
                        path: str = f"{REGISTRY_REPO_PATH}/specs/latest/man/html/{data}"
                        if os.path.exists(path):
                                return open(path, 'r', encoding="utf-8").read()
                
                return ""
        
        indent: int        = 1 if useNamespace else 0
        soup               = BeautifulSoup(get_html(name), "html.parser")
        mainHeader: Tag    = soup.find('h1')
        content: Tag       = soup.find('div', id='content')
        nameTitle: Tag     = mainHeader.find_next('h2')
        nameParagraph: Tag = mainHeader.find_next('div', class_="sectionbody")
        
        # Check if any of the required divs are missing.
        if not all([mainHeader, content, nameTitle, nameParagraph]):
                return name, ""
        
        try:
                documentation = DocumentationBlock(name, style, indent)
                documentation.add(nameTitle)
                documentation.add(nameParagraph, type="paragraph")
        
                def should_print(e: Tag) -> bool:
                        return e.find('h2').get_text(strip=True) not in NOT_PRINTED_DIVS
        
                for section in filter(should_print, content.find_all('div', class_="sect1")):
                        documentation.add(section)
        except Exception as e:
                raise RuntimeError(f"{e}\n\nError generating documentation for '{name}'.")
        
        # Returning name to easily construct a dictionary later
        return name, documentation.value


def __call_generate(args: tuple[str, Style, bool]):
        return get_element_documentation(*args)


def generate_documentations(style: Style, useNamespace: bool) -> dict[str, str]:
        base: str = f"{REGISTRY_REPO_PATH}/specs/latest/man/html/"
        
        def make_arg(path: str) -> tuple[str, Style, bool]:
                from pathlib import Path
                return Path(path).stem, style, useNamespace
        
        args: list = [make_arg(path) for path in os.listdir(base) if path.startswith("Vk") or path.startswith("vk") or path.startswith("VK_")]
        with ProcessPoolExecutor() as executor:
                docs: dict = dict(list(executor.map(__call_generate, args)))
        
        return docs


def write_file_documentation(outputPath: str, path: str, docs: dict[str, str], style: Style, useNamespace: bool) -> None:
        with open(path, 'r', encoding="utf-8") as f:
                data: str = f.read()
        
        # Remove all the comments in header
        data = re.sub(COMMENT_REGEX, '', data)
        
        def add_documentation(match: Match[str], name: str, function: bool = False, macro: bool = False) -> str:
                def camel_case(string: str) -> str:
                        return string[0].lower() + string[1:]
                
                # Some headers may use elements without documentation, if so return
                # the whole match.
                if name not in docs:
                        return match.group(0)
                
                # Macros don't get redefined in the namespace.
                if macro:
                        return docs[name] + match.group(0)
                
                if not useNamespace:
                        # If not in the namespace, just add the documentation
                        # before.
                        return docs[name] + match.group(0)
                else:
                        text: str = f"auto constexpr {camel_case(name[2:])}" if function else f"using {name[2:]}"
                        return match.group(0) + f"namespace vk {{\n{docs[name]}    {text} = {name};\n}}\n"
        
        # TODO fix macros in TXT mode.
        if style != Style.TXT:
                data = re.sub(DEFINITION_REGEX, lambda match: add_documentation(match, match.group(1), macro=True), data)
        
        data = re.sub(HANDLE_REGEX, lambda match: add_documentation(match, match.group(3) or match.group(5)), data)
        data = re.sub(FUNCTION_REGEX, lambda match: add_documentation(match, match.group(2), function=True), data)
        data = re.sub(TYPEDEF_REGEX, lambda match: add_documentation(match, match.group(2)), data)
        
        # Extra fixes to apply to the whole file
        data = re.sub(r"\n\n+", "\n\n", data)
        
        with open(path, 'w', encoding='utf-8') as f:
                f.write(data)
        
        os.rename(path, f"{outputPath}/vulkan/{os.path.basename(path)}")


def __call_write(args: tuple[str, str, dict, Style, bool]) -> None:
        write_file_documentation(*args)


def write_documentation(outputPath: str, docs: dict[str, str], style: Style, useNamespace: bool) -> None:
        base: str = f"{HEADERS_REPO_PATH}/include/vulkan"
        
        def make_arg(path: str) -> tuple[str, str, dict, bool]:
                return outputPath, f"{base}/{path}", docs, style, useNamespace
                
        args: list = [make_arg(path) for path in os.listdir(base) if path.endswith(".h")]
        with ProcessPoolExecutor() as executor:
                executor.map(__call_write, args)


def main(outputPath: str, style: Style, useNamespace: bool) -> None:
        start: float  = time()
        regen, output = should_regenerate(outputPath)
        
        if not regen:
                print(f"Action completed in {time() - start}s")
                return
        
        print("Downloading headers and registry...")
        subprocess.run(["git", "clone",
                        "https://github.com/KhronosGroup/Vulkan-Headers.git",
                        *CLONE_ARGS, HEADERS_REPO_PATH], check=True)
        subprocess.run(["git", "clone",
                        "https://github.com/KhronosGroup/Vulkan-Registry.git",
                        *CLONE_ARGS, REGISTRY_REPO_PATH], check=True)

        prepare_environment(outputPath)

        print("Generating the documentation and headers...")
        docs: dict = generate_documentations(style, useNamespace)
        write_documentation(outputPath, docs, style, useNamespace)
        
        print("Clearing downloaded content...")
        shutil.rmtree(HEADERS_REPO_PATH, onexc=onerror)
        shutil.rmtree(REGISTRY_REPO_PATH, onexc=onerror)
        
        with open(VERSION_FILE, 'w', encoding="utf-8") as f:
                f.write(output)
        
        print(f"Action completed in {time() - start}s")


if __name__ == "__main__":
        assert sys.version_info >= (3, 12), "Script requires Python 3.12 or newer."
        assert sys.argv[1], "Script must be run with the output path as its first argument"
        
        outputPath: str    = sys.argv[1]
        style: Style       = Style.CL
        useNamespace: bool = False
        
        # Delete headers and registry directories if already present
        for path in [HEADERS_REPO_PATH, REGISTRY_REPO_PATH]:
                if os.path.exists(path):
                        shutil.rmtree(path, onexc=onerror)
        
        # Check all given flags
        for flag in sys.argv[2:]:
                if flag in ['-' + e.name for e in Style]:
                        style = Style[flag[1:]]
                elif flag == "-N":
                        useNamespace = True
                elif flag == "--force":
                        if os.path.exists(VERSION_FILE):
                                os.remove(VERSION_FILE)
                else:
                        raise Exception(f"Unknown flag '{flag}' given.")
        
        # If flag is valid pass the flag without the '-'
        main(outputPath, style, useNamespace)

# TODO fix images https://registry.khronos.org/vulkan/specs/latest/man/html/VkPrimitiveTopology.html
