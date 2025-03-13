import re
import os
import sys
import html
import stat
import shutil
import requests
import subprocess

from time import time
from enum import Enum
from typing import Final
from pathlib import Path
from types import NoneType
from requests import Response
from bs4 import BeautifulSoup, NavigableString, Tag
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor


class Style(Enum):
        """
        The program acceptable styles
        """
        
        TXT = -1  # Plain text
        
        CL = 0    # CLion
        RS = 1    # ReSharper
        VSC = 2   # Visual Studio Code


# Constants
VULKAN_VALID_USAGE: Final = "https://raw.githubusercontent.com/KhronosGroup/Vulkan-Registry/refs/heads/main/specs/latest/validation/validusage.json"
VULKAN_REGISTRY: Final    = "https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/"
VERSION_FILE: Final       = "./.version.txt"
NOT_PRINTED_DIVS: Final   = ["Document Notes", "See Also", "Copyright"]
THREADS: Final            = os.cpu_count()
CHAR_FIX_MAP: Final       = { "\\rfloor": '⌋', "\\lfloor": '⌊', "\\times": '×', "\\(": '', "\\)": '' }
HEADERS_REPO_PATH: Final  = "./.hds"
REGISTRY_REPO_PATH: Final = "./.rex"

# Regexes
HANDLE_REGEX: Final   = re.compile(r"^((VK_DEFINE_HANDLE\(([^\n)]+)\))\n|(VK_DEFINE_NON_DISPATCHABLE_HANDLE\(([^\n)]+)\))\n(?!```))", re.MULTILINE)
FUNCTION_REGEX: Final = re.compile(r"^(VKAPI_ATTR [^\n ]+ VKAPI_CALL (vk[^ \n]+)\([^;]+);\n(?!```)", re.MULTILINE)
TYPEDEF_REGEX: Final  = re.compile(r"^(typedef [^ \n]+ (Vk[^ \n]+)( {\n[^}]+} [^;]+)?;\n(?!```))", re.MULTILINE)


class DocumentationBlock:
        def __init__(self, url: str, style: Style, indentLevel: int) -> None:
                self.__STYLE = style
                self.__URL = url
                self.__INDENT_LEVEL = indentLevel
                self.__PREFIX = self.__INDENT_LEVEL * "    " + " * "
                self.add_dd = self.add_li if self.__STYLE == Style.CL else self.add_sub_elements
        
        def add(self, element, singleLine: bool = False, listLevel: int = 0):
                """
                Generic method to add an element to the documentation
                :param element: the HTML element
                :param singleLine: if the element is in a single line
                :param listLevel: the level of indentation
                """
                assert element, "Invalid element passed to add"
                
                if isinstance(element, NavigableString):
                        self.add_sub_elements(element, singleLine, listLevel)
                        return
                
                name: str = element.name
                if name == "div":
                        name = ' '.join(element.get('class', []))

                re.sub("[^a-zA-Z0-9_]", '_', name)
                
                function = getattr(self, f"add_{name}", None)
                if function:
                        function(element, singleLine, listLevel)
                else:
                        # If the type is unknown, add the element children
                        self.add_sub_elements(element, singleLine, listLevel)
        
        def add_formatted(self, string: str, singleLine: bool, listLevel: int) -> None:
                """
                Generic method to add a string to the documentation
                :param string: the string to add
                :param singleLine: if the element is in a single line
                :param listLevel: the level of indentation
                """
                if not singleLine:
                        self.__value += self.__getBase(listLevel)
                
                self.__value += string
                
                if not singleLine:
                        self.__value += '\n'
        
        def add_sub_elements(self, element, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds all the element sub-elements to the documentation
                :param element: the HTML element with the sub-elements
                :param singleLine: if the element is in a single line
                :param listLevel: the level of indentation
                """
                assert element, "Invalid element given to 'add_sub_elements'"
                
                # If an element only contains text
                if isinstance(element, NavigableString):
                        if element.strip() != "":
                                # Remove the whitespace at the begin of the string only
                                # if it's not already empty
                                PREF: str = ' ' if self.__value != "" and self.__value[-1] not in [' ', '⠀'] else ''
                                
                                text: str = re.sub(r"^[ \n]+", f"{PREF}", element)
                                
                                # Some text areas contain extra spaces, invisible in the website
                                text = text.replace('\n', ' ')
                                self.__value += re.sub(r"  +", ' ', text)
                        
                        return
                
                # If not we cycle through all of its children
                for subElement in element.contents:
                        self.add(subElement, singleLine, listLevel)
        
        #                                        #
        # -------------- ELEMENTS -------------- #
        #                                        #
        
        def add_a(self, anchor, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds an anchor element to the documentation
                :param anchor: the anchor element
                :param singleLine: if the anchor is in a single line
                :param listLevel: the level of indentation
                """
                assert anchor, "Invalid element given to 'add_a'"
                
                if not singleLine:
                        self.__value += self.__getBase(listLevel)
                
                RETURN_REPLACE: str = f"{f"{"<br>\n" if self.__STYLE == Style.CL else '\n'}" if not singleLine else ''}"
                
                # We keep the href only if it's a valid link
                if anchor.has_attr('href') and self.__STYLE not in [Style.RS, Style.TXT]:
                        # Cannot use anchor in ReSharper
                        
                        CONTENT: str = anchor['href'].strip()
                        if CONTENT.startswith("http"):
                                # Direct link
                                text: str = anchor.getText(strip=True).replace('\n', RETURN_REPLACE)
                                link: str = CONTENT
                        elif CONTENT.startswith("#"):
                                # Relative link
                                text: str = anchor.getText(strip=True).replace('\n', RETURN_REPLACE)
                                link: str = f"{self.__URL}{CONTENT}"
                        elif CONTENT.endswith(".html"):
                                # Relative file link
                                text: str = anchor.getText(strip=True).replace('\n', RETURN_REPLACE)
                                link: str = f"{VULKAN_REGISTRY}{CONTENT}"
                        else:
                                raise Exception("Unknown anchor href given to 'addAnchor'")
                        
                        if self.__STYLE == Style.CL:
                                self.__value += f"<a href=\"{link}\">{text}</a>"
                        else:
                                text = text if text != "" else "↖ "
                                self.__value += f"[{text}]({link})"
                else:
                        # Anchor without link gets printed as text
                        self.__value += f"{anchor.getText(strip=True).replace('\n', RETURN_REPLACE)}"
                
                if not singleLine:
                        self.__value += '\n'
        
        def add_br(self, _unused1: NoneType = None, _unused2: NoneType = None, listLevel: int = 0) -> None:
                """
                Adds a break element to the documentation
                :param listLevel: the level of indentation
                """
                if self.__STYLE == Style.CL:
                        # Only CLion requires a break the <br> element
                        self.__value += "<br>"
                
                self.__value += "\n" + self.__getBase(listLevel)
        
        def add_code(self, code, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a code element to the documentation
                :param code: the code element
                :param singleLine: if the code is in a single line
                :param listLevel: the level of indentation
                """
                assert code, "Invalid element given to 'add_code'"
                
                if self.__STYLE in [Style.CL, Style.RS]:
                        self.add_formatted(f"<b>{code.getText(strip=True).replace('\n', '')}</b>", singleLine, listLevel)
                else:
                        # Visual Studio Code does not support html nor markdown bold or italic
                        self.add_formatted(f"{code.getText(strip=True).replace('\n', '')}", singleLine, listLevel)
        
        def add_dt(self, definitionTerm, _unused: NoneType = None, listLevel: int = 0) -> None:
                """
                Adds a definition term element to the documentation
                :param definitionTerm: the definition term element
                :param listLevel: the level of indentation
                """
                assert definitionTerm, "Invalid element given to 'add_dt'"
                
                text: str = definitionTerm.getText(strip=True)
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
                        # The empty chars are different, also uses h4 markdown
                        self.__value += f"{self.__PREFIX}{listLevel * "⠀⠀"}#### ⠀{text}\n{self.__PREFIX}\n"
        
        def add_em(self, emphasized, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds an emphasized element to the documentation
                :param emphasized: the emphasized element
                :param singleLine: if the emphasized element is in a single line
                :param listLevel: the level of indentation
                """
                assert emphasized, "Invalid element given to 'add_em'"
                
                if self.__STYLE in [Style.CL, Style.RS]:
                        self.add_formatted(f"<i>{emphasized.getText(strip=True).replace('\n', '')}</i>", singleLine, listLevel)
                else:
                        # Visual Studio Code does not support html nor markdown bold or italic
                        self.add_formatted(f"{emphasized.getText(strip=True).replace('\n', '')}", singleLine, listLevel)
        
        def add_ulist(self, list, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a list element to the documentation
                :param list: the list element
                :param singleLine: if the list is in a single line
                :param listLevel: the level of indentation
                """
                assert list, "Invalid element given to 'add_list'"
                
                TYPE: Final = f"{list.get('class', [])[0][0]}l"
                
                if singleLine:
                        self.__value += '\n'
                
                if self.__STYLE == Style.CL:
                        self.__value += f"{self.__PREFIX}{listLevel * "    "}<{TYPE}>\n"
                        self.add_sub_elements(list, listLevel=listLevel + 1)
                else:
                        self.add_sub_elements(list, listLevel=listLevel)
                        return
                
                self.__value += f"{self.__PREFIX}{listLevel * "    "}</{TYPE}>"
                
                if singleLine:
                        return
                
                self.__value += f"\n{self.__PREFIX}\n"
        
        add_dlist = add_ulist
        
        def add_li(self, listEntry, _unused: NoneType = None, listLevel: int = 0) -> None:
                """
                Adds a list entry element to the documentation
                :param listEntry: the list entry element
                :param listLevel: the level of indentation
                """
                assert listEntry, "Invalid element given to 'add_li'"
                
                match self.__STYLE:
                        case Style.CL:
                                self.__value += f"{self.__PREFIX}{listLevel * "    "}<{listEntry.name}>"
                        case Style.RS:
                                self.__value += f"{self.__PREFIX}{listLevel * "  "}- "
                        case _:
                                # Visual Studio Code does not support nested list, so we add 4 U+2800 '⠀' after the -
                                self.__value += f"{self.__PREFIX}- {listLevel * "⠀  ⠀"}"
                
                self.add_sub_elements(listEntry, True, listLevel + 1)
                
                if self.__value[-1] != '\n':
                        # If the last element added by 'addSubElements' didn't add a
                        # return, add it here
                        self.__value += '\n'
        
        def add_span(self, span, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a span element to the documentation
                :param span: the span element
                :param singleLine: if the span is in a single line
                :param listLevel: the level of indentation
                """
                assert span, "Invalid element given to 'add_span'"
                
                text: str = span.getText(strip=True)
                if span.get('class') and span.get('class') == ['eq']:
                        # eq class span are math expressions
                        tmpDoc = DocumentationBlock(self.__URL, self.__STYLE, self.__INDENT_LEVEL)
                        tmpDoc.add_sub_elements(span, True)
                        text = tmpDoc.__value
                
                if text.strip() == "":
                        return
                
                if singleLine:
                        self.__value += f"{text.replace('\n', ' ')}"
                        return
                
                self.__value += self.__getBase(listLevel) + f"{text.replace('\n', ' ')}"
        
        def add_strong(self, strong, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a strong element to the documentation
                :param strong: the strong element
                :param singleLine: if the strong element is in a single line
                :param listLevel: the level of indentation
                """
                assert strong, "Invalid element given to 'add_strong'"
                
                # Sometimes there is not a space between text and a <strong>
                if self.__value != "" and self.__value[-1] != ' ':
                        self.__value += ' '
                
                match self.__STYLE:
                        case Style.CL:
                                self.add_formatted(f"<i><b>{strong.getText(strip=True).replace('\n', ' ')}</b></i>", singleLine, listLevel)
                        case Style.RS:
                                # ReSharper breaks bold italic, so we only use bold
                                self.add_formatted(f"<b>{strong.getText(strip=True).replace('\n', ' ')}</b>", singleLine, listLevel)
                        case _:
                                # Visual Studio Code does not support html nor markdown bold or italic
                                self.add_formatted(f"{strong.getText(strip=True).replace('\n', ' ')}", singleLine, listLevel)
        
        def add_sub(self, sub, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                """
                Adds a sub element to the documentation
                :param sub: the sub element
                """
                assert sub, "Invalid element given to 'add_sub'"
                
                # Get all subtext
                tmpDoc = DocumentationBlock(self.__URL, self.__STYLE, self.__INDENT_LEVEL)
                tmpDoc.add_sub_elements(sub, True)
                
                if self.__STYLE in [Style.CL, Style.RS]:
                        self.__value += "<sub>" + tmpDoc.__value + "</sub>"
                else:
                        self.__value += tmpDoc.__value
        
        def add_table(self, table, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                """
                Adds a table element to the documentation
                :param table: the table element
                """
                assert table, "Invalid element given to 'add_table'"
                
                # Tables are not supported with the ReSharper option.
                if self.__STYLE in [Style.RS, Style.TXT]:
                        return
                
                # Removes whitespace and breaks, adds spaces when needed
                def fixHTML(item: Tag) -> str:
                        for br in item.find_all("br"):
                                br.replace_with('\n')
                        
                        text: str = ''.join(str(content) for content in item.contents)
                        
                        # Remove html, extra '\n' and ' '
                        text = re.sub(r"\s*\n\s*", '\n', text.strip())
                        text = re.sub(r"<([^<>])+>", '', text)
                        text = re.sub(r"( )+", ' ', text)
                        
                        return html.unescape(text)
                
                headElements = table.find('thead').find('tr').find_all('th') if table.find('thead') else table.find_all('tr')[0].find_all('td')
                headers: list[str] = [fixHTML(cell) for cell in headElements]
                rows: list[list[str]] = [[fixHTML(cell) for cell in tr.find_all(['th', 'td'])] for tr in table.find_all('tr')[1:]]
                
                # Adding empty cells when needed
                for row in rows:
                        while len(row) < len(headers):
                                row.append('')
                
                columns: list[list[str]] = [headers] + rows
                columnsWidths: list[int] = [max(len(line) for cell in col for line in cell.split('\n')) + 2 for col in zip(*columns)]
                
                # Print the table with proper formatting
                def format_row(row: list[str]) -> list[str]:
                        if self.__STYLE == Style.CL:
                                formattedLines: list[list[str]] = [cell.split('\n') for cell in row]
                                return [(
                                        f"{self.__PREFIX}|  "
                                        # The :<{columnsWidths[cellIdx] - 2}}>
                                        # specifies the padding
                                        + '  |  '.join([f'{(lines[lineIdx] if lineIdx < len(lines) else ''):<{columnsWidths[cellIdx] - 2}}' for cellIdx, lines in enumerate(formattedLines)])
                                        + "  |<br>"
                                ) for lineIdx in range(max(len(lines) for lines in formattedLines))]
                        else:
                                # The fake bar is unicode U+FF5C '｜'
                                return [f"{self.__PREFIX}|｜ {' |｜ '.join(row).replace('\n', ', ')} |｜ |"]
                
                BREAK_LINE: str = self.__PREFIX + '-' * (sum(columnsWidths) + 3 * len(columnsWidths) + 1) + "<br>"
                
                # The whole table, initialized with the headers
                if self.__STYLE == Style.CL:
                        tableRows: list[str] = [BREAK_LINE, *format_row(headers), BREAK_LINE]
                else:
                        # Adding an extra column for the closing bar
                        tableRows: list[str] = [*format_row(headers), self.__PREFIX + ''.join(["| :-- " for _ in headers]) + '| :-- |']
                
                # Adds all the rows
                for row in rows:
                        tableRows.extend(format_row(row))
                        if self.__STYLE == Style.CL:
                                tableRows.append(BREAK_LINE)
                
                # Saves the table
                if self.__STYLE == Style.CL:
                        self.__value += f"{self.__PREFIX}<pre>\n"
                
                self.__value += '\n'.join(tableRows) + '\n'
                
                if self.__STYLE == Style.CL:
                        self.__value += f"{self.__PREFIX}</pre><br>\n{self.__PREFIX}\n"
        
        #                                        #
        # ---------------- DIVS ---------------- #
        #                                        #
        
        def add_listingblock(self, listingblock, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                """
                Adds a listingblock div to the documentation
                :param listingblock: the listingblock div
                """
                assert listingblock, "Invalid element given to 'add_listingblock'"
                
                if self.__STYLE in [Style.CL, Style.RS]:
                        self.__value += f"{self.__PREFIX}@code\n"
                        self.__value += f"{self.__PREFIX}{listingblock.find('pre').getText(strip=True).replace('\n', f"\n{self.__PREFIX}")}\n"
                        self.__value += f"{self.__PREFIX}@endcode\n{self.__PREFIX}\n"
                elif self.__STYLE == Style.VSC:
                        SPACES: str = self.__INDENT_LEVEL * "    "
                        
                        # Visual studio does not support the @code or <code> tag
                        self.__value += f"```c\n"
                        self.__value += f"{SPACES}{listingblock.find('pre').getText(strip=True).replace('\n', f"\n{SPACES}")}\n"
                        self.__value += f"```\n{self.__PREFIX}\n"
                else:
                        self.__value += f"{self.__PREFIX}\n"
                        self.__value += f"{self.__PREFIX}{listingblock.find('pre').getText(strip=True).replace('\n', f"\n{self.__PREFIX}")}\n"
                        self.__value += f"{self.__PREFIX}\n"
        
        def add_sidebarblock(self, sidebarblock, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                assert sidebarblock, "Invalid element given to 'add_sidebarblock'"
                self.add_sub_elements(sidebarblock.find('div', 'content'))
        
        add_sectionbody = add_sub_elements
        
        def add_paragraph(self, paragraph, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a paragraph div to the documentation
                :param paragraph: the paragraph div
                :param singleLine: if the paragraph is in a single line
                :param listLevel: the level of indentation
                """
                assert paragraph, "Invalid element given to 'add_paragraph'"
                
                # Some styles require a safety check to ensure that
                # the paragraph has something at its left
                if not singleLine or self.__value[-1] == '\n':
                        self.__value += self.__getBase(listLevel)
                
                self.add_sub_elements(paragraph, True)
                
                match self.__STYLE:
                        case Style.CL:
                                self.__value += "<br><br>"
                        case Style.RS:
                                self.__value += "<br>"
                
                if not singleLine:
                        self.__value += f"\n{self.__PREFIX}\n"
        
        def add_h2(self, title, _unused1: NoneType = None, _unused2: NoneType = None) -> None:
                """
                Adds a title div to the documentation
                :param title: the title div
                """
                assert title, "Invalid element given to 'add_title'"
                
                if self.__value != "":
                        if self.__STYLE == Style.CL:
                                # Add a <br> after lists if before a title
                                START: int = len("</ul>\n * \n") + self.__INDENT_LEVEL * 4
                                END: int = START + len("</ul>")
                                if self.__value[-START:-END] == "</ul>" or self.__value[-START:-END] == "</dl>":
                                        self.__value = self.__value[:-9] + f"<br>\n{self.__PREFIX}\n{self.__PREFIX}"
                        elif self.__value[-3:] != "* \n" and self.__value[-3:] != "**\n":
                                # If there is not an empty line add one
                                self.__value += f"{self.__PREFIX}\n"
                
                self.__value += f"{self.__PREFIX}"
                if self.__STYLE == Style.VSC:
                        # To correctly render the header, it needs to be before everything else
                        self.__value += "## "
                
                if title.find('a'):
                        self.add_a(title.find('a'), True)
                
                match self.__STYLE:
                        case Style.CL:
                                self.__value += f"<b>{title.getText(strip=True).replace('\n', ' ')}</b><hr>"
                        case Style.RS:
                                self.__value += f"<b>{title.getText(strip=True).replace('\n', ' ')}</b><br>"
                        case _:
                                self.__value += f"{title.getText(strip=True).replace('\n', ' ')}"
                
                self.__value += f"\n{self.__PREFIX}\n"
        
        add_title = add_h2
        
        #                                        #
        # ---------------- PRIV ---------------- #
        #                                        #
        
        def __getBase(self, listLevel: int) -> str:
                match self.__STYLE:
                        case Style.CL:
                                return f"{self.__PREFIX}{listLevel * "    "}"
                        case Style.RS:
                                # ReSharper uses markdown lists
                                return f"{self.__PREFIX}{listLevel * "  "}"
                        case _:
                                # The empty chars are different
                                return f"{self.__PREFIX}{listLevel * "⠀⠀"}"
        
        #                                        #
        # --------------- STATE ---------------- #
        #                                        #
        
        __value: str = ""
        __URL: str = ""
        __STYLE: Style = Style.CL
        __INDENT_LEVEL: int = 0
        __PREFIX: str = ""
        
        @property
        def value(self) -> str:
                # Not working with '__value' directly
                string: str = self.__value
                
                # Fix invalid chars
                for old, new in CHAR_FIX_MAP.items():
                        string = string.replace(old, new)
                
                # Class arguments dependant constants
                SPACE_COUNT: int = self.__INDENT_LEVEL * 4
                EMPTY_LINE_REGEX: str = rf" {{{SPACE_COUNT + 1}}}\* "
                
                if self.__STYLE in [Style.CL, Style.RS]:
                        # Remove break before code block
                        string = re.sub(rf"(<br>)+(\n{EMPTY_LINE_REGEX}\n {{{SPACE_COUNT + 1}}}\* @code)", r"\2", string)
                        
                        # Fix sub-text
                        string = re.sub(r"(?<=[\s,.=])([a-zA-Z])_([a-zA-Z]+)(?=[\s,.=])", r"\1<sub>\2</sub>", string)
                else:
                        def simulateSubText(match: re.Match[str]) -> str:
                                return match.group(1).upper() + match.group(2)
                        
                        # Fix sub-text
                        string = re.sub(r"(?<=[\s,.=])([a-zA-Z])_([a-zA-Z]+)(?=[\s,.=])", simulateSubText, string)
                
                # Extra CLion specific fixes
                if self.__STYLE == Style.CL:
                        # Remove space after list entry begin
                        string = string.replace("<li> ", "<li>")
                        
                        # Merge adjacent lists
                        string = string.replace(f"{self.__PREFIX}</ul>\n{self.__PREFIX}\n{self.__PREFIX}<ul>\n", "")
                        string = string.replace(f"{self.__PREFIX}</dl>\n{self.__PREFIX}\n{self.__PREFIX}<dl>\n", "")
                
                # Remove extra whitespace
                string = re.sub(rf"{EMPTY_LINE_REGEX}\n( {{{SPACE_COUNT + 1}}}\* \n)", r"\1", string)
                string = re.sub(rf"(({EMPTY_LINE_REGEX})( {{4}})+)( +)?", r"\1", string)
                
                if self.__STYLE == Style.RS:
                        string = re.sub(r"(@endcode[ \n*]+)<br>", r"\1", string)
                
                if self.__STYLE == Style.VSC:
                        # Visual studio documentation may be broken as it contains many
                        # '*' and math expressions
                        string = string.replace("*/", "* /")
                        string = string.replace("/*", "/ *")
                
                if self.__STYLE == Style.TXT:
                        SPACES_COUNT: int = self.__INDENT_LEVEL * 4
                        string = re.sub(rf"^ {{{SPACES_COUNT}}} \* ", '', string, flags=re.MULTILINE)
                
                PREFIX: str = f"{self.__INDENT_LEVEL * "    "}/**\n"
                SUFFIX: str = f"{self.__INDENT_LEVEL * "    "}*/\n"
                
                # Documentation end
                if string[-3:] == "* \n":
                        # Avoid adding empty line
                        string = string[:-2] + "/\n"
                else:
                        string += SUFFIX
                
                return PREFIX + string


def get_version() -> str:
        """
        Gets the current Vulkan version
        :return: the version as a string
        """
        request: Response = requests.get(VULKAN_VALID_USAGE)
        data: dict = request.json()
        version: str = data["version info"]["api version"]
        
        return version


def should_regenerate(current: str, outputPath: str) -> bool:
        VERSION: str = current.split(" ")[0]
        
        if os.path.exists(VERSION_FILE) and os.path.exists(outputPath):
                with open(VERSION_FILE, 'r', encoding="utf-8") as f:
                        DATA: str = f.read()
                
                if DATA == current:
                        print(f"Current headers match the most recent version of Vulkan ({VERSION}) and use the correct flags. Not generating.")
                        return False
                
                if DATA.split(' ')[0] == VERSION:
                        print(f"Current headers match the most recent version of Vulkan ({VERSION}), but use the wrong flags.")
                else:
                        print(f"Current headers (v {DATA[0]}) do not match the most recent version of Vulkan ({VERSION}).")
                
                os.remove(VERSION_FILE)
                
        return True


def onerror(func, path: str, _) -> None:
        if not os.access(path, os.W_OK):
                # Change file permission
                os.chmod(path, stat.S_IWUSR)
                func(path)
        else:
                # If error is not due to permission issues, raise
                raise Exception("Could not delete cloned directory.")


def prepare_environment(outputPath: str) -> None:
        """
        Deletes all directories and files and creates new empty ones
        :param outputPath: the output path
        """
        # If output path is a new directory
        if os.path.exists(outputPath):
                shutil.rmtree(outputPath, onexc=onerror)
        
        # Create new empty output directory, move vk_video since it has no
        # documentation.
        os.mkdir(outputPath)
        os.mkdir(outputPath + "/vulkan/")
        os.rename(f"{HEADERS_REPO_PATH}/include/vk_video/", f"{outputPath}/vk_video")


def get_HTML(name: str) -> str:
        """
        Reads the HTML file of the provided element
        :param name: the name of the element
        """
        PATH: Final = f"{REGISTRY_REPO_PATH}/specs/latest/man/html/{name}.html"
        assert os.path.exists(PATH), f"Could not find HTML file for '{name}'"
        
        with open(PATH, 'r', encoding="utf-8") as f:
                DATA: Final = f.read()
                
                # Some files may redirect to others
                if len(DATA) <= 256 and os.path.exists(f"{REGISTRY_REPO_PATH}/specs/latest/man/html/{DATA}"):
                        return open(f"{REGISTRY_REPO_PATH}/specs/latest/man/html/{DATA}", 'r', encoding="utf-8").read()
                
                return DATA


def get_element_documentation(name: str, style: Style, useNamespace: bool) -> tuple[str, str]:
        """
        Returns the code ready documentation for the given element
        :param name: the name of the element
        :param style: the script platform style
        :param useNamespace: if the header should be generated with namespace aliases
        """
        # When not using the namespace aliases, the documentation is above the
        # element, and it does not require any indentation.
        INDENT: Final = 1 if useNamespace else 0
        
        SOUP: Final        = BeautifulSoup(get_HTML(name), "html.parser")
        mainHeader: Tag    = SOUP.find('h1')
        content: Tag       = SOUP.find('div', id='content')
        nameTitle: Tag     = mainHeader.find_next('h2')
        nameParagraph: Tag = mainHeader.find_next('div', class_="sectionbody")
        
        # Check if any of the required divs are missing.
        if not any([mainHeader, content, nameTitle, nameParagraph]):
                return name, ""
        
        documentation = DocumentationBlock(f"{VULKAN_REGISTRY}{name}.html", style, INDENT)
        
        documentation.add(nameTitle)
        documentation.add_paragraph(nameParagraph)
        
        # Filter out predetermined divs
        SECTIONS: list = [sect for sect in content.find_all('div', class_="sect1") if sect.find('h2').get_text(strip=True) not in NOT_PRINTED_DIVS]
        
        # Add all sub-divs
        for section in SECTIONS:
                documentation.add(section)
        
        # Returning name to easily construct a dictionary later
        return name, documentation.value


def _get_element_documentation(args: tuple[str, Style, bool]):
        return get_element_documentation(*args)


def generate_documentations(style: Style, useNamespace: bool) -> dict[str, str]:
        """
        Generates all the documentations in a multithreaded environment
        :param style: the script platform style
        :param useNamespace: if the header should be generated with namespace aliases
        :return: A dictionary { name: documentation } containing all the documentations
        """
        PATH: Final = f"{REGISTRY_REPO_PATH}/specs/latest/man/html/"
        ARGS: Final = [(Path(file).stem, style, useNamespace) for file in os.listdir(PATH) if file.startswith("Vk") or file.startswith("vk")]
        
        with ProcessPoolExecutor() as executor:
                docs: dict[str, str] = dict(list(executor.map(_get_element_documentation, ARGS)))
        
        return docs


def write_file_documentation(outputPath: str, path: str, docs: dict[str, str], useNamespace: bool) -> None:
        """
        Writes all the documentation with the given platform style
        :param outputPath: the output path
        :param path: the current header to update.
        :param docs: the documentations dictionary
        :param useNamespace: if the header should be generated with namespace aliases
        """
        with open(path, 'r', encoding="utf-8") as f:
                data: str = f.read()
        
        def add_documentation(match: re.Match[str], name: str, isFunction: bool) -> str:
                def camel_case(string: str) -> str:
                        return string[0].lower() + string[1:]
                
                # Some headers may use handles without documentation
                if name not in docs:
                        return match.group(0)
                
                if not useNamespace:
                        return docs[name] + match.group(0)
                else:
                        TEXT: str = f"auto constexpr {camel_case(name[2:])}" if isFunction else f"using {name[2:]}"
                        return match.group(0) + f"namespace vk {{\n{docs[name]}    {TEXT} = {name};\n}}\n"
        
        # Add all the elements documentations
        data = re.sub(HANDLE_REGEX, lambda match: add_documentation(match, match.group(3) or match.group(5), False), data)
        data = re.sub(FUNCTION_REGEX, lambda match: add_documentation(match, match.group(2), True), data)
        data = re.sub(TYPEDEF_REGEX, lambda match: add_documentation(match, match.group(2), False), data)
        
        # Extra fixes to apply to the whole file
        data = re.sub(r"\n\n+", "\n\n", data)
        
        with open(path, 'w', encoding='utf-8') as f:
                f.write(data)
        
        os.rename(path, f"{outputPath}/vulkan/{os.path.basename(path)}")


def write_documentation(outputPath: str, docs: dict[str, str], useNamespace: bool) -> None:
        # Adds the documentation to all headers
        FILES: Final = [path for path in os.listdir(f"{HEADERS_REPO_PATH}/include/vulkan/") if path.endswith(".h")]
        
        def write_function(file: str) -> None:
                write_file_documentation(outputPath, f"{HEADERS_REPO_PATH}/include/vulkan/{file}", docs, useNamespace)
        
        with ThreadPoolExecutor() as executor:
                executor.map(write_function, FILES)


def main(outputPath: str, style: Style, useNamespace: bool) -> None:
        INIT_TIME: float = time()
        VERSION: str = get_version()
        
        OUT_STRING: str = f"{VERSION} {style} {useNamespace}"
        if not should_regenerate(OUT_STRING, outputPath):
                print(f"Action completed in {time() - INIT_TIME}s")
                return
        
        print("Downloading headers and registry...")
        CLONE_ARGS: Final = [ "--branch", "main", "--single-branch", "--depth", "1", "--quiet" ]
        subprocess.run(["git", "clone", "https://github.com/KhronosGroup/Vulkan-Headers.git", *CLONE_ARGS, HEADERS_REPO_PATH], check=True)
        subprocess.run(["git", "clone", "https://github.com/KhronosGroup/Vulkan-Registry.git", *CLONE_ARGS, REGISTRY_REPO_PATH], check=True)

        prepare_environment(outputPath)

        print("Generating the documentation and headers...")
        DOCS: Final = generate_documentations(style, useNamespace)
        write_documentation(outputPath, DOCS, useNamespace)
        
        print("Clearing downloaded content...")
        shutil.rmtree(HEADERS_REPO_PATH, onexc=onerror)
        shutil.rmtree(REGISTRY_REPO_PATH, onexc=onerror)
        
        with open(VERSION_FILE, 'w', encoding="utf-8") as f:
                f.write(OUT_STRING)
        
        print(f"Action completed in {time() - INIT_TIME}s")


if __name__ == "__main__":
        assert sys.argv[1], "Script must be run with the output path as its first argument"
        _outputPath: str = sys.argv[1]
        
        # All optional flags with their default value, using _ prefix since
        # this is in global namespace and intellisense errors bother me
        _style: Style = Style.CL
        _useNamespace: bool = False
        
        # Check all given flags
        for flag in sys.argv[2:]:
                if flag in ['-' + e.name for e in Style]:
                        _style = Style[flag[1:]]
                elif flag == "-N":
                        _useNamespace = True
                else:
                        raise Exception(f"Unknown flag '{flag}' given.")
        
        # If flag is valid pass the flag without the '-'
        main(_outputPath, _style, _useNamespace)
