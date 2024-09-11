import re
import os
import sys
import pip
import html
import math
import stat
import shutil
import hashlib
import requests
import threading
import subprocess

from re import Match
from time import time
from enum import Enum
from threading import Thread
from requests import Response


class Style(Enum):
        """
        The program acceptable styles
        """

        TXT = -1  # Plain text

        CL = 0    # CLion
        RS = 1    # ReSharper
        VSC = 2   # Visual Studio Code


# Constants
VULKAN_REGISTRY: str = "https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/"
NOT_PRINTED_DIVS: list[str] = ["Document Notes", "See Also", "Copyright"]
THREADS: int = os.cpu_count()
CHAR_FIX_MAP: dict[str, str] = {
        "\\rfloor": '⌋',
        "\\lfloor": '⌊',
        "\\times": '×',
        "\\(": '',
        "\\)": ''
}

# Global variables
VALID_ELEMENTS: list[str] = []

# Regexes
HANDLE_REGEX = re.compile(r"^((VK_DEFINE_HANDLE\(([^\n)]+)\))\n|(VK_DEFINE_NON_DISPATCHABLE_HANDLE\(([^\n)]+)\))\n(?!```))", re.MULTILINE)
FUNCTION_REGEX = re.compile(r"^(VKAPI_ATTR [^\n ]+ VKAPI_CALL (vk[^ \n]+)\([^;]+);\n(?!```)", re.MULTILINE)
TYPEDEF_REGEX = re.compile(r"^(typedef [^ \n]+ (Vk[^ \n]+)( {\n[^}]+} [^;]+)?;\n(?!```))", re.MULTILINE)


class DocumentationBlock:
        def __init__(self, url: str, style: Style, indentLevel: int) -> None:
                self.__STYLE = style
                self.__URL = url
                self.__INDENT_LEVEL = indentLevel
                self.__PREFIX = self.__INDENT_LEVEL * "    " + " * "

        def addRaw(self, string: str):
                """
                Adds a string to the documentation
                :param string: the string to add
                """
                self.__value += string

        def addString(self, string: str, singleLine: bool, listLevel: int) -> None:
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

        def addElement(self, element, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Generic method to add an element to the documentation
                :param element: the HTML element
                :param singleLine: if the element is in a single line
                :param listLevel: the level of indentation
                """
                assert element, "Invalid element given to 'addElement'"

                match element.name:
                        case 'a':
                                self.addAnchor(element, singleLine, listLevel)
                        case 'em':
                                self.addEmphasized(element, singleLine, listLevel)
                        case 'h2':
                                self.addTitle(element)
                        case 'dt':
                                self.addDefinitionTerm(element, listLevel)
                        case 'dd':
                                if self.__STYLE == Style.CL:
                                        # Only CLion supports dlist correctly
                                        self.addListEntry(element, "dd", listLevel)
                                else:
                                        self.addSubElements(element, singleLine, listLevel)
                        case 'li':
                                self.addListEntry(element, "li", listLevel)
                        case 'br':
                                self.addBreak(listLevel)
                        case 'sub':
                                self.addSub(element)
                        case 'code':
                                self.addCode(element, singleLine, listLevel)
                        case 'span':
                                self.addSpan(element, singleLine, listLevel)
                        case 'strong':
                                self.addStrong(element, singleLine, listLevel)
                        case 'table':
                                self.addTable(element)
                        case 'div':
                                # Only some type of divs are supported
                                match ' '.join(element.get('class', [])):
                                        case 'title':
                                                self.addTitle(element)
                                        case 'paragraph':
                                                self.addParagraph(element, singleLine, listLevel)
                                        case 'listingblock':
                                                self.addListingblock(element)
                                        case 'ulist':
                                                self.addList(element, 'u', singleLine, listLevel)
                                        case 'dlist':
                                                self.addList(element, 'd', singleLine, listLevel)
                                        case 'sidebarblock':
                                                self.addSubElements(element.find('div', 'content'))
                                        case 'admonitionblock note':
                                                self.addNote(element, listLevel)
                                        case 'sectionbody':
                                                self.addSubElements(element, singleLine, listLevel)
                        case _:
                                # If the type is not recognized, we cycle through its children
                                self.addSubElements(element, singleLine, listLevel)

        def addSubElements(self, element, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds all the element sub-elements to the documentation
                :param element: the HTML element with the sub-elements
                :param singleLine: if the element is in a single line
                :param listLevel: the level of indentation
                """
                assert element, "Invalid element given to 'addSubElements'"

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
                        self.addElement(subElement, singleLine, listLevel)

        #                                        #
        # -------------- ELEMENTS -------------- #
        #                                        #

        def addAnchor(self, anchor, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds an anchor element to the documentation
                :param anchor: the anchor element
                :param singleLine: if the anchor is in a single line
                :param listLevel: the level of indentation
                """
                assert anchor, "Invalid element given to 'addAnchor'"

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
                                assert False, "Unknown anchor href given to 'addAnchor'"

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

        def addBreak(self, listLevel: int = 0) -> None:
                """
                Adds a break element to the documentation
                :param listLevel: the level of indentation
                """
                if self.__STYLE == Style.CL:
                        # Only CLion requires a break the <br> element
                        self.__value += "<br>"

                self.__value += "\n" + self.__getBase(listLevel)

        def addCode(self, code, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a code element to the documentation
                :param code: the code element
                :param singleLine: if the code is in a single line
                :param listLevel: the level of indentation
                """
                assert code, "Invalid element given to 'addCode'"

                if self.__STYLE in [Style.CL, Style.RS]:
                        self.addString(f"<b>{code.getText(strip=True).replace('\n', '')}</b>", singleLine, listLevel)
                else:
                        # Visual Studio Code does not support html nor markdown bold or italic
                        self.addString(f"{code.getText(strip=True).replace('\n', '')}", singleLine, listLevel)

        def addDefinitionTerm(self, definitionTerm, listLevel: int = 0) -> None:
                """
                Adds a definition term element to the documentation
                :param definitionTerm: the definition term element
                :param listLevel: the level of indentation
                """
                assert definitionTerm, "Invalid element given to 'addDefinitionTerm'"

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

        def addEmphasized(self, emphasized, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds an emphasized element to the documentation
                :param emphasized: the emphasized element
                :param singleLine: if the emphasized element is in a single line
                :param listLevel: the level of indentation
                """
                assert emphasized, "Invalid element given to 'addEmphasized'"

                if self.__STYLE in [Style.CL, Style.RS]:
                        self.addString(f"<i>{emphasized.getText(strip=True).replace('\n', '')}</i>", singleLine, listLevel)
                else:
                        # Visual Studio Code does not support html nor markdown bold or italic
                        self.addString(f"{emphasized.getText(strip=True).replace('\n', '')}", singleLine, listLevel)

        def addList(self, list, listType: str, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a list element to the documentation
                :param list: the list element
                :param listType: the list type char (u/d)
                :param singleLine: if the list is in a single line
                :param listLevel: the level of indentation
                """
                assert list, "Invalid element given to 'addList'"

                if singleLine:
                        self.__value += '\n'

                if self.__STYLE == Style.CL:
                        self.__value += f"{self.__PREFIX}{listLevel * "    "}<{listType}l>\n"
                        self.addSubElements(list, listLevel=listLevel + 1)
                else:
                        self.addSubElements(list, listLevel=listLevel)
                        return

                self.__value += f"{self.__PREFIX}{listLevel * "    "}</{listType}l>"

                if singleLine:
                        return

                self.__value += f"\n{self.__PREFIX}\n"

        def addListEntry(self, listEntry, entryType: str, listLevel: int = 0) -> None:
                """
                Adds a list entry element to the documentation
                :param listEntry: the list entry element
                :param entryType: the type of list entry
                :param listLevel: the level of indentation
                """
                assert listEntry, "Invalid element given to 'addListEntry'"

                match self.__STYLE:
                        case Style.CL:
                                self.__value += f"{self.__PREFIX}{listLevel * "    "}<{entryType}>"
                        case Style.RS:
                                self.__value += f"{self.__PREFIX}{listLevel * "  "}- "
                        case _:
                                # Visual Studio Code does not support nested list, so we add 4 U+2800 '⠀' after the -
                                self.__value += f"{self.__PREFIX}- {listLevel * "⠀  ⠀"}"

                self.addSubElements(listEntry, True, listLevel + 1)

                if self.__value[-1] != '\n':
                        # If the last element added by 'addSubElements' didn't add a
                        # return, add it here
                        self.__value += '\n'

        def addSpan(self, span, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a span element to the documentation
                :param span: the span element
                :param singleLine: if the span is in a single line
                :param listLevel: the level of indentation
                """
                assert span, "Invalid element given to 'addSpan'"

                text: str = span.getText(strip=True)
                if span.get('class') and span.get('class') == ['eq']:
                        # eq class span are math expressions
                        tmpDoc = DocumentationBlock(self.__URL, self.__STYLE, self.__INDENT_LEVEL)
                        tmpDoc.addSubElements(span, True)
                        text = tmpDoc.__value

                if text.strip() == "":
                        return

                if singleLine:
                        self.__value += f"{text.replace('\n', ' ')}"
                        return

                self.__value += self.__getBase(listLevel) + f"{text.replace('\n', ' ')}"

        def addStrong(self, strong, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a strong element to the documentation
                :param strong: the strong element
                :param singleLine: if the strong element is in a single line
                :param listLevel: the level of indentation
                """
                assert strong, "Invalid element given to 'addStrong'"

                # Sometimes there is not a space between text and a <strong>
                if self.__value != "" and self.__value[-1] != ' ':
                        self.__value += ' '

                match self.__STYLE:
                        case Style.CL:
                                self.addString(f"<i><b>{strong.getText(strip=True).replace('\n', ' ')}</b></i>", singleLine, listLevel)
                        case Style.RS:
                                # ReSharper breaks bold italic, so we only use bold
                                self.addString(f"<b>{strong.getText(strip=True).replace('\n', ' ')}</b>", singleLine, listLevel)
                        case _:
                                # Visual Studio Code does not support html nor markdown bold or italic
                                self.addString(f"{strong.getText(strip=True).replace('\n', ' ')}", singleLine, listLevel)

        def addSub(self, sub) -> None:
                """
                Adds a sub element to the documentation
                :param sub: the sub element
                """
                assert sub, "Invalid element given to 'addSub'"

                # Get all subtext
                tmpDoc = DocumentationBlock(self.__URL, self.__STYLE, self.__INDENT_LEVEL)
                tmpDoc.addSubElements(sub, True)

                if self.__STYLE in [Style.CL, Style.RS]:
                        self.__value += "<sub>" + tmpDoc.__value + "</sub>"
                else:
                        self.__value += tmpDoc.__value

        def addTable(self, table) -> None:
                """
                Adds a table element to the documentation
                :param table: the table element
                """
                assert table, "Invalid element given to 'addTable'"

                # Tables are not supported with the ReSharper option.
                if self.__STYLE in [Style.RS, Style.TXT]:
                        return

                # Removes whitespace and breaks, adds spaces when needed
                def fixHTML(item: Tag) -> str:
                        for br in item.findAll("br"):
                                br.replace_with('\n')

                        text: str = ''.join(str(content) for content in item.contents)

                        # Remove html, extra '\n' and ' '
                        text = re.sub(r"\s*\n\s*", '\n', text.strip())
                        text = re.sub(r"<([^<>])+>", '', text)
                        text = re.sub(r"( )+", ' ', text)

                        return html.unescape(text)

                headElements = table.find('thead').find('tr').findAll('th') if table.find('thead') else table.findAll('tr')[0].findAll('td')
                headers: list[str] = [fixHTML(cell) for cell in headElements]
                rows: list[list[str]] = [[fixHTML(cell) for cell in tr.findAll(['th', 'td'])] for tr in table.findAll('tr')[1:]]

                # Adding empty cells when needed
                for row in rows:
                        while len(row) < len(headers):
                                row.append('')

                columns: list[list[str]] = [headers] + rows
                columnsWidths: list[int] = [max(len(line) for cell in col for line in cell.split('\n')) + 2 for col in zip(*columns)]

                # Print the table with proper formatting
                def format_row(row: list[str]) -> list[str]:
                        if self.__STYLE == Style.CL:
                                formatted_lines: list[list[str]] = [cell.split('\n') for cell in row]
                                return [(
                                        f"{self.__PREFIX}|  {'  |  '.join([f'{(lines[line_index] if line_index < len(lines) else '')
                                        :<{columnsWidths[cell_index] - 2}}' for cell_index, lines in enumerate(formatted_lines)])}  |<br>"
                                ) for line_index in range(max(len(lines) for lines in formatted_lines))]
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

        def addListingblock(self, listingblock) -> None:
                """
                Adds a listingblock div to the documentation
                :param listingblock: the listingblock div
                """
                assert listingblock, "Invalid element given to 'addListingblock'"

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

        def addNote(self, note, listLevel: int = 0) -> None:
                """
                Adds a note div to the documentation
                :param note: the note div
                :param listLevel: the level of indentation
                """
                table: Tag = note.find('table')
                assert table, "Invalid element given to 'addNote'"

                tr: Tag = table.find('tr')
                assert tr, "Invalid element given to 'addNote'"

                td: Tag = tr.find('td', class_='content')
                assert td, "Invalid element given to 'addNote'"

                if listLevel != 0:
                        self.__value += '\n'

                self.__value += self.__getBase(listLevel)

                # ReSharper changes how the @note tag works, breaking it.
                if self.__STYLE in [Style.CL, Style.VSC]:
                        self.__value += "@note "

                for paragraph in td.findAll('div', class_='paragraph'):
                        self.addSubElements(paragraph, True)

                self.__value += f"\n{self.__PREFIX}"

                if listLevel == 0:
                        self.__value += "\n"

        def addParagraph(self, paragraph, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a paragraph div to the documentation
                :param paragraph: the paragraph div
                :param singleLine: if the paragraph is in a single line
                :param listLevel: the level of indentation
                """
                assert paragraph, "Invalid element given to 'addParagraph'"

                # Some styles require a safety check to ensure that
                # the paragraph has something at its left
                if not singleLine or self.__value[-1] == '\n':
                        self.__value += self.__getBase(listLevel)

                self.addSubElements(paragraph, True)

                match self.__STYLE:
                        case Style.CL:
                                self.__value += "<br><br>"
                        case Style.RS:
                                self.__value += "<br>"

                if not singleLine:
                        self.__value += f"\n{self.__PREFIX}\n"

        def addTitle(self, title) -> None:
                """
                Adds a title div to the documentation
                :param title: the title div
                """
                assert title, "Invalid element given to 'addTitle'"

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
                        self.addAnchor(title.find('a'), True)

                match self.__STYLE:
                        case Style.CL:
                                self.__value += f"<b>{title.getText(strip=True).replace('\n', ' ')}</b><hr>"
                        case Style.RS:
                                self.__value += f"<b>{title.getText(strip=True).replace('\n', ' ')}</b><br>"
                        case _:
                                self.__value += f"{title.getText(strip=True).replace('\n', ' ')}"

                self.__value += f"\n{self.__PREFIX}\n"

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


def getDocumentationFromURL(version: str, url: str, style: Style, useNamespace: bool) -> str:
        """
        Function to parse and extract the required information
        :param version: the current Vulkan version
        :param url: the url to get the html from
        :param style: the script platform style
        :param useNamespace: if the header should be generated with namespace aliases
        """
        htmlText: str = fetchHTML(version, url)
        soup = BeautifulSoup(htmlText, "html.parser")

        mainHeader: Tag = soup.find('h1')
        assert mainHeader, f"Could not find main header for URL '{url}'"

        content: Tag = soup.find('div', id='content')
        assert content, f"Could not find content div for URL '{url}'"

        # When not using the namespace aliases, the documentation is above the
        # element, and it does not require any indentation
        indentLevel: int = 1 if useNamespace else 0
        documentation = DocumentationBlock(url, style, indentLevel)

        # Add name header
        nameTitle: Tag = mainHeader.findNext('h2')
        assert nameTitle, f"Could not find name header for URL '{url}'"
        documentation.addTitle(nameTitle)

        # Add name paragraph
        nameParagraph: Tag = mainHeader.findNext('div', class_="sectionbody")
        assert nameParagraph, f"Could not find name paragraph for URL '{url}'"
        documentation.addParagraph(nameParagraph)

        # Filter out predetermined divs
        SECTIONS: list = [sect for sect in content.findAll('div', class_="sect1") if sect.find('h2').getText(strip=True) not in NOT_PRINTED_DIVS]

        # Add all sub-divs
        for section in SECTIONS:
                documentation.addSubElements(section)

        return documentation.value


def writeDocumentation(outputPath: str, version: str, file: str, style: Style, useNamespace: bool) -> None:
        """
        Writes all the documentation with the given platform style
        :param outputPath: the output path
        :param version: the current Vulkan version
        :param file: the current header to update.
        :param style: the script platform style
        :param useNamespace: if the header should be generated with namespace aliases
        """
        with open(file, 'r', encoding="utf-8") as f:
                data: str = f.read()

        def addDoc(match: re.Match[str], name: str, isFunction: bool) -> str:
                def getRegistryURL(string: str) -> str:
                        return f"{VULKAN_REGISTRY}{string}.html"

                def firstLetterToLower(string: str) -> str:
                        return string[0].lower() + string[1:]

                # Some headers may use handles without documentation
                if name not in VALID_ELEMENTS:
                        return match.group(0)

                # The element URL, would cause an error with an invalid element
                URL: str = getRegistryURL(name)

                # The element documentation
                DOCUMENTATION: str = getDocumentationFromURL(version, URL, style, useNamespace)

                if not useNamespace:
                        return DOCUMENTATION + match.group(0)
                else:
                        TEXT: str = f"auto constexpr {firstLetterToLower(name[2:])}" if isFunction else f"using {name[2:]}"
                        return match.group(0) + f"namespace vk {{\n{DOCUMENTATION}    {TEXT} = {name};\n}}\n"

        # Add all the elements documentations
        data = re.sub(HANDLE_REGEX, lambda match: addDoc(match, match.group(3) or match.group(5), False), data)
        data = re.sub(FUNCTION_REGEX, lambda match: addDoc(match, match.group(2), True), data)
        data = re.sub(TYPEDEF_REGEX, lambda match: addDoc(match, match.group(2), False), data)

        # Extra fixes to apply to the whole file
        data = data.replace("#include \"vk_video/", "#include \"../vk_video/")
        data = re.sub(r"\n\n+", "\n\n", data)

        with open(file, 'w', encoding='utf-8') as f:
                f.write(data)

        os.rename(file, outputPath + "/vulkan/" + os.path.basename(file))


def getVersion() -> str:
        """
        Gets the current Vulkan version
        :return: the version as a string
        """
        with open("./tmp/registry/validusage.json", 'r', encoding='utf-8') as f:
                DATA: str = f.read()

        return re.search(r"\"api version\": \"([1-9.]+)\"", DATA).group(1)


def fetchHTML(version: str, url: str) -> str:
        """
        Fetches the HTML content of a URL
        :param version: the current Vulkan version
        :param url: the url to fetch
        :return: the HTML content as a string
        """
        def createHashName() -> str:
                return str(int(hashlib.sha1(url.encode("utf-8")).hexdigest(), 16) % (10 ** 8))

        SEARCH: Match[str] = re.search(r"\/(?:.(?!\/))+$", url)
        NAME: str = SEARCH.group(0) if SEARCH else f"/unknown{createHashName()}.html"

        # File must be an HTML file
        if not NAME.endswith(".html"):
                NAME += ".html"

        # If cached file does not exist, fetch the HTML content
        if not os.path.exists(f"./.v{version}/{NAME}"):
                response: Response = requests.get(url)

                # Raise an error for bad status codes
                response.raise_for_status()
                response.encoding = "utf-8"

                with open(f"./.v{version}/{NAME}", 'w', encoding='utf-8') as file:
                        file.write(response.text)

                return response.text

        with open(f"./.v{version}/{NAME}", 'r', encoding='utf-8') as file:
                return file.read()


def getValidElements(version: str) -> list[str]:
        """
        Gets all the valid elements from vulkan registry
        :param version: the current Vulkan version
        :return: the valid elements as a list of strings
        """
        REGISTRY: str = fetchHTML(version, VULKAN_REGISTRY)
        soup = BeautifulSoup(REGISTRY, "html.parser")

        files: Tag = soup.find('div', id='files')
        assert files, "Could not get 'files' div"

        table: Tag = files.find('table')
        assert table, "Could not find table"

        cells: ResultSet[Tag] = table.select('td a')
        assert cells, "Could not find element names"

        elements: list[str] = []
        for cell in cells:
                text: str = cell.getText(strip=True)

                # Skip invalid elements
                if not (text.startswith("Vk") or text.startswith("vk")):
                        continue

                elements.append(os.path.splitext(text)[0])

        # Split the elements into 1 chunks per thread
        CHUNK_SIZE: int = math.ceil(len(elements) / THREADS)
        CHUNKS: list[list[str]] = [elements[i:i + CHUNK_SIZE] for i in range(0, len(elements), CHUNK_SIZE)]

        def threadFunction(chunk: list[str]) -> None:
                [fetchHTML(version, f"{VULKAN_REGISTRY}{name}.html") for name in chunk]

        # Download all elements now
        threads: list[Thread] = []
        for i in range(THREADS):
                thread: Thread = threading.Thread(target=threadFunction, args=(CHUNKS[i],))
                threads.append(thread)
                thread.start()

        # Wait for all threads to complete
        for thread in threads:
                thread.join()

        return elements


def prepareEnvironment(outputPath: str, version: str) -> None:
        """
        Deletes all directories and files and creates new empty ones
        :param outputPath: the output path
        :param version: the current Vulkan version
        """
        if not os.path.exists(f"./.v{version}/"):
                print("Cached HTML files directory not found.")

                # Remove different version cached files
                for item in os.listdir("./"):
                        path: str = os.path.join("./", item)
                        if item.startswith(".v") and os.path.isdir(path):
                                shutil.rmtree(path)

                os.mkdir(f"./.v{version}/")
        else:
                print("Cached HTML files directory found.")

        # If output path is a new directory
        if not os.path.exists(outputPath):
                os.mkdir(outputPath)

        os.mkdir(outputPath + "/vulkan/")


def main(outputPath: str, style: Style, useNamespace: bool) -> None:
        INIT_TIME: float = time()

        # Download original headers
        subprocess.run(["git", "clone", "https://github.com/KhronosGroup/Vulkan-Headers.git", "--branch", "main", "--single-branch", "./tmp"], check=True)

        # The version as string, since it's not a valid float
        VERSION: str = getVersion()
        print(f"Writing documentation for vulkan from url '{VULKAN_REGISTRY}', version: '{VERSION}'...")

        # Create and delete directories
        prepareEnvironment(outputPath, VERSION)

        # Gets all valid elements
        global VALID_ELEMENTS
        VALID_ELEMENTS = getValidElements(VERSION)

        # Move vk_video directory
        shutil.move("./tmp/include/vk_video/", outputPath)

        # Adds the documentation to all headers
        FILES: list[str] = [path for path in os.listdir("./tmp/include/vulkan/") if path.endswith(".h")]
        CHUNK_COUNT: int = max(len(FILES) // THREADS, 1)
        REMAINDER: int = len(FILES) % CHUNK_COUNT

        def threadFunction(i: int) -> None:
                START: int = i * CHUNK_COUNT + min(i, REMAINDER)
                END: int = START + CHUNK_COUNT + (1 if i < REMAINDER else 0)

                for j in range(START, END):
                        writeDocumentation(outputPath, VERSION, "./tmp/include/vulkan/" + FILES[j], style, useNamespace)

        threads: list[Thread] = []
        for i in range(THREADS):
                thread: Thread = threading.Thread(target=threadFunction, args=(i,))
                threads.append(thread)
                thread.start()

        # Wait for all threads to complete
        for thread in threads:
                thread.join()

        # Delete fetched headers
        def onerror(func, path: str, _) -> None:
                if not os.access(path, os.W_OK):
                        # Change file permission
                        os.chmod(path, stat.S_IWUSR)
                        func(path)
                else:
                        # If error is not due to permission issues, raise
                        assert False, "Could not delete cloned directory."

        shutil.rmtree("./tmp", onexc=onerror)

        print(f"Documentation extracted and written in {time() - INIT_TIME}s")


if __name__ == "__main__":
        print("Generating headers with flags: ", sys.argv[2:])

        try:
                # Try to import bs4
                __import__("bs4")
        except ImportError:
                # If bs4 is not installed, install it
                pip.main(["install", "bs4"])

        # Now that bs4 is imported, import dependencies
        from bs4 import BeautifulSoup, NavigableString, Tag, ResultSet

        assert sys.argv[1], "Script must be run with the output path as its first argument"
        _output_path: str = sys.argv[1]

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
                        assert False, f"Unknown flag '{flag}' given."

        # If flag is valid pass the flag without the '-'
        main(_output_path, _style, _useNamespace)
