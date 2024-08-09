import re
import os
import sys
import math
import html
import hashlib
import requests
import threading

from time import time
from threading import Lock, Thread
from bs4 import BeautifulSoup, NavigableString

# Constants
VULKAN_REGISTRY: str = "https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/"
VULKAN_VERSION_CHECK: str = "https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VK_API_VERSION.html"
OUTPUT_FILE: str = "../vulkan++.hpp"
THREADS: int = 16
HEADER_HTML_REGEX: str = r" {9}\* <b>[A-Za-z0-9 ()]+<\/b><hr><br>\n"
HEADER_MD_REGEX: str = r" {9}\* [a-zA-Z ]+\n {9}\* ---\n"
EMPTY_LINE_REGEX: str = r" {9}\* \n"
CHAR_FIX_MAP: dict[str, str] = {
        "\\rfloor": '⌋',
        "\\lfloor": '⌊',
        "\\times": '×',
        "\\(": '',
        "\\)": ''
}
ANCHOR_FIX_MAP: dict[str, str] = {
        "<code>": "<b>",
        "</code>": "</b>",
        '\n': ' '
}
DEFAULT_PROVIDERS: list[str] = ["VK_VERSION_1_0", "VK_VERSION_1_1", "VK_VERSION_1_2", "VK_VERSION_1_3"]

# Global variables
VALID_ELEMENTS: list[str] = list()
USED_NAMES: list[str] = list()
VERSION: str = ""

# Regex
FIX_SUBSTRINGS_REGEX = re.compile(r"(?<=[\s,.=])([a-zA-Z])_([a-zA-Z]+)(?=[\s,.=])")
REMOVE_EXTRAS_REGEX = re.compile(r"(((" + EMPTY_LINE_REGEX + r")*" + HEADER_HTML_REGEX + r")|(((<br>)+)(?=\n)))?(\n?)(" + EMPTY_LINE_REGEX + r")+(?=( {8}\*\/))")
REMOVE_BREAKS_BEFORE_ELEMENTS_REGEX = re.compile(r"(<br>)+\n(" + EMPTY_LINE_REGEX + r")*( {9}\* (@|(<dl>)|(<ul>)|(<pre>)))")
REMOVE_EXTRA_WHITESPACE_REGEX = re.compile(r"^( {9}\* )(?!\|)(( {4})*)(.*)$", re.MULTILINE)
REMOVE_EMPTY_LINES_REGEX = re.compile(r"(" + EMPTY_LINE_REGEX + ")*(" + EMPTY_LINE_REGEX + ")")
REMOVE_EMPTY_LINE_AFTER_DEFINITION_TERM_REGEX = re.compile(r"(<dd>)(\n {9}\* (?: {4})*)")
REMOVE_EMPTY_HEADERS_MD_REGEX = re.compile(r"(" + HEADER_MD_REGEX + ")*(" + HEADER_MD_REGEX + ")")
FIND_VERSION_REGEX = re.compile(r"(?<=Version )([\d.]+)")
FIND_NAME_FROM_URL_REGEX = re.compile(r"\/(?:.(?!\/))+$")
FIND_NAME_FROM_HEADER_REGEX = re.compile(r"^[a-zA-Z0-9]+")
FIND_PROVIDERS_HTML_REGEX = re.compile(r"@code\n {9}\* \/\/ Provided by ((?:[a-zA-Z0-9_]+(?: with [a-zA-Z0-9_]+)?(?:, )?)+)")
FIND_PROVIDERS_MD_REGEX = re.compile(r"```c\n {4}\/\/ Provided by ((?:[a-zA-Z0-9_]+(?: with [a-zA-Z0-9_]+)?(?:, )?)+)")

class Cache:
        def __init__(self, url: str, html: bool) -> None:
                self.__HTML = html
                self.__URL = url

        def write(self, file) -> None:
                """
                Writes the cached value to the given file
                :param file: the file to write into
                """
                string = self.__value

                # Fix math
                for old, new in CHAR_FIX_MAP.items():
                        string = string.replace(old, new)

                if self.__HTML:
                        string = re.sub(FIX_SUBSTRINGS_REGEX, r"\1<sub>\2</sub>", string)
                        string = re.sub(REMOVE_EXTRAS_REGEX, r"\7", string)
                else:
                        string = re.sub(FIX_SUBSTRINGS_REGEX, lambda match: f"{match.group(1).upper()}{match.group(2)}", string)

                # Removes empty headers, empty lines and breaks before the end of the documentation
                string = re.sub(r"\n+", '\n', string)

                # Remove extra spaces
                def removeExtraWhitespace(match) -> str:
                        return f"{match.group(1)}{match.group(2) or ''}{re.sub(r' {2,}', ' ', match.group(4)).strip()}"

                string = re.sub(REMOVE_EXTRA_WHITESPACE_REGEX, removeExtraWhitespace, string)
                string = string.replace(" , ", ", ")

                if self.__HTML:
                        string = re.sub(REMOVE_EMPTY_LINE_AFTER_DEFINITION_TERM_REGEX, r"\1", string)
                        string = re.sub(REMOVE_BREAKS_BEFORE_ELEMENTS_REGEX, r"\n\2\3", string)

                        # Remove space after list entry begin
                        string = string.replace("<li> ", "<li>")

                        # Merge adjacent lists
                        string = string.replace("         * </ul>\n         * \n         * <ul>\n", "")
                        string = string.replace("         * </dl>\n         * \n         * <dl>\n", "")
                else:
                        string = re.sub(REMOVE_EMPTY_HEADERS_MD_REGEX, r"\2", string)
                        string = string.replace("         * -\n", '')
                        string = re.sub(REMOVE_EMPTY_LINES_REGEX, r"\2", string)
                        string = string.replace("         * \n        */", "        */")

                # Writes the fixed cache
                file.write(string)

        #                                        #
        # -------------- ELEMENTS -------------- #
        #                                        #

        def addAnchor(self, anchor, prefix: str = '', singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds an anchor element to the cache
                :param anchor: the anchor element
                :param prefix: the prefix string
                :param singleLine: if the anchor is in a single line
                :param listLevel: the level of indentation
                """
                if not singleLine:
                        if self.__HTML:
                                self.__value += f"         * {listLevel * "    "}"
                        else:  # Empty chars are different
                                self.__value += f"         * {listLevel * "⠀⠀⠀⠀"}"
                                
                if not self.__HTML:
                        self.__value += f"{prefix}{anchor.getText(strip=True).replace('\n', ' ')}"

                        if not singleLine:
                                self.__value += '\n'

                        return

                # We keep the href only if it's a valid link
                if anchor.has_attr('href'):
                        content = anchor['href'].strip()
                        if content.startswith("http"):
                                text: str = str(anchor)
                                for old, new in ANCHOR_FIX_MAP.items():
                                        text = text.replace(old, new)
                                self.__value += f"{prefix} {text}"
                        elif content.startswith("#"):
                                text: str = anchor.getText(strip=True).replace('\n', ' ')
                                self.__value += f"{prefix} <a href=\"{self.__URL}{content}\">{text}</a>"
                else:
                        self.__value += f"{prefix}{anchor.getText(strip=True).replace('\n', ' ')}"

                if not singleLine:
                        self.__value += '\n'

        def addBreak(self, singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a break element to the cache
                :param singleLine: if the break is in a single line
                :param listLevel: the level of indentation
                """
                if self.__HTML:
                        self.__value += "<br>"

                self.__value += "\n"
                if singleLine:
                        self.__value += f"         * {listLevel * "    "}"

        def addCode(self, code, prefix: str = '', singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a code element to the cache
                :param code: the code element
                :param prefix: the prefix string
                :param singleLine: if the code is in a single line
                :param listLevel: the level of indentation
                """
                if not code:
                        return

                if self.__HTML:
                        self.addGeneric(f"<b>{code.getText(strip=True).replace('\n', ' ')}</b>", prefix, singleLine, listLevel)
                else:
                        self.addGeneric(code.getText(strip=True).replace('\n', ' '), prefix, singleLine, listLevel)

        def addDefinitionTerm(self, definitionTerm, prefix: str = '', listLevel: int = 0) -> None:
                """
                Adds a definition term element to the cache
                :param definitionTerm: the definition term element
                :param prefix: the prefix string
                :param listLevel: the level of indentation
                """
                if not definitionTerm:
                        return

                text = definitionTerm.getText(strip=True)
                if text.strip() == "":
                        return

                if self.__HTML:
                        self.__value += f"         * {listLevel * "    "}{prefix}<dt>{text}\n"
                else:  # The spaces after "####" are 1 space and 1 unicode U+2800 '⠀'
                        self.__value += f"         * \n         * {listLevel * "⠀⠀⠀⠀"}{prefix}#### ⠀{text}\n         * \n"

        def addEmphasized(self, emphasized, prefix: str = '', singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds an emphasized element to the cache
                :param emphasized: the emphasized element
                :param prefix: the prefix string
                :param singleLine: if the emphasized element is in a single line
                :param listLevel: the level of indentation
                """
                if not emphasized:
                        return

                if self.__HTML:
                        self.addGeneric(f"<i>{emphasized.getText(strip=True).replace('\n', ' ')}</i>", prefix, singleLine, listLevel)
                else:
                        self.addGeneric(emphasized.getText(strip=True).replace('\n', ' '), prefix, singleLine, listLevel)

        def addGeneric(self, string: str, prefix: str, singleLine: bool, listLevel: int) -> None:
                """
                Generic method to add a string to the documentation
                :param string: the string to add
                :param prefix: the prefix string
                :param singleLine: if the element is in a single line
                :param listLevel: the level of indentation
                """
                if not singleLine:
                        if self.__HTML:
                                self.__value += f"         * {listLevel * "    "}"
                        else:
                                self.__value += f"         * {listLevel * "⠀⠀⠀⠀"}"

                self.__value += prefix + string
                if not singleLine:
                        self.__value += '\n'

        def addList(self, list, listType: str, prefix: str = '', singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a list element to the cache
                :param list: the list element
                :param prefix: the prefix string
                :param listType: the list type char (u/d)
                :param singleLine: if the list is in a single line
                :param listLevel: the level of indentation
                """
                if not list:
                        return

                if singleLine:
                        self.__value += '\n'

                if self.__HTML:
                        self.__value += f"         * {listLevel * "    "}{prefix}<{listType}l>\n"

                getHTML(list, self, prefix, listLevel=listLevel + (1 if self.__HTML else 0))

                if not self.__HTML:
                        self.__value += "         * \n"
                        return

                self.__value += f"         * {listLevel * "    "}{prefix}</{listType}l>"

                if singleLine:
                        return

                self.__value += "\n"

                if prefix == '':
                        self.__value += "         * \n"

        def addListEntry(self, listEntry, entryType: str, prefix: str = '', listLevel: int = 0) -> None:
                """
                Adds a list entry element to the cache
                :param listEntry: the list entry element
                :param entryType: the type of list entry
                :param prefix: the prefix string
                :param listLevel: the level of indentation
                """
                if self.__HTML:
                        self.__value += f"         * {listLevel * "    "}{prefix}<{entryType}>"
                else:  # Since VS is shit, it does not support nested list, so we add 4 U+2800 '⠀' after the -
                        self.__value += f"         * {prefix} - {listLevel * "⠀⠀⠀⠀"}"

                getHTML(listEntry, self, singleLine=True, listLevel=listLevel + 1)

                self.__value += '\n'
                if not self.__HTML:
                        self.__value += "         * \n"

        def addRaw(self, string: str):
                """
                Adds a string to the cache
                :param string: the string to add
                """
                self.__value += string

        def addSpan(self, span, prefix: str = '', singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a span element to the cache
                :param span: the span element
                :param prefix: the prefix string
                :param singleLine: if the span is in a single line
                :param listLevel: the level of indentation
                """
                if not span:
                        return

                text: str = span.getText(strip=True)
                if span.get('class') and span.get('class') == ['eq']:
                        tempCache = Cache(self.__URL, self.__HTML)
                        getHTML(span, tempCache, singleLine=True)
                        text = tempCache.__value

                if text.strip() == "":
                        return

                if not singleLine:
                        if self.__HTML:
                                self.__value += f"         * {listLevel * "    "}"
                        else:
                                self.__value += f"         * {listLevel * "⠀⠀⠀⠀"}"

                self.__value += f"{prefix}{text.replace('\n', ' ')}"

        def addStrong(self, strong, prefix: str = '', singleLine: bool = False, listLevel: int = 0) -> None:
                """
                Adds a strong element to the cache
                :param strong: the strong element
                :param prefix: the prefix string
                :param singleLine: if the strong element is in a single line
                :param listLevel: the level of indentation
                """
                if not strong:
                        return

                if self.__HTML:
                        self.addGeneric(f" <i><b>{strong.getText(strip=True).replace('\n', ' ')}</b></i>", prefix, singleLine, listLevel)
                else:
                        self.addGeneric(f" {strong.getText(strip=True).replace('\n', ' ')}", prefix, singleLine, listLevel)

        def addSub(self, sub) -> None:
                """
                Adds a sub element to the cache
                :param sub: the sub element
                """
                tempCache = Cache(self.__URL, self.__HTML)
                getHTML(sub, tempCache, singleLine=True)
                if self.__HTML:
                        self.__value += "<sub>" + tempCache.__value + "</sub>"
                else:
                        self.__value += tempCache.__value

        def addTable(self, table) -> None:
                """
                Adds a table element to the cache
                :param table: the table element
                """
                if not table:
                        return

                # Removes whitespace and breaks, adds spaces when needed
                def fixHTML(item) -> str:
                        for br in item.findAll("br"):
                                br.replace_with('\n')

                        text = ''.join(str(content) for content in item.contents)

                        # Remove html, extra '\n' and ' '
                        text = re.sub(r"\s*\n\s*", '\n', text.strip())
                        text = re.sub(r"<([^<>])+>", '', text)
                        text = re.sub(r"( )+", ' ', text)

                        return html.unescape(text)

                headElements = table.find('thead').find('tr').findAll('th') if table.find('thead') else table.findAll('tr')[0].findAll('td')
                headers = [fixHTML(cell) for cell in headElements]
                rows = [[fixHTML(cell) for cell in tr.findAll(['th', 'td'])] for tr in table.findAll('tr')[1:]]

                # Adding empty cells when needed
                for row in rows:
                        while len(row) < len(headers):
                                row.append('')

                columns: list[list[str]] = [headers] + rows
                columnsWidths: list[int] = [max(len(line) for cell in col for line in cell.split('\n')) + 2 for col in zip(*columns)]

                # Print the table with proper formatting
                def format_row(row: list[str]) -> list[str]:
                        if self.__HTML:
                                formatted_lines: list[list[str]] = [cell.split('\n') for cell in row]
                                return [(
                                        f"         * |  {'  |  '.join([f'{(lines[line_index] if line_index < len(lines) else '')
                                        :<{columnsWidths[cell_index] - 2}}' for cell_index, lines in enumerate(formatted_lines)])}  |<br>"
                                ) for line_index in range(max(len(lines) for lines in formatted_lines))]
                        else:  # The fake bar is unicode U+FF5C '｜'
                                return [f"         * |｜ {' |｜ '.join(row).replace('\n', ', ')} |｜ |"]

                breakLine: str = "         * " + '-' * (sum(columnsWidths) + 3 * len(columnsWidths) + 1) + "<br>"

                # The whole table, initialized with the headers
                tableRows: list[str] = []
                if self.__HTML:
                        tableRows = [breakLine, *format_row(headers), breakLine]
                else:
                        # Adding an extra column for the closing bar
                        tableRows = [*format_row(headers), "         * " + ''.join(["| :-- " for _ in headers]) + '| :-- |']

                # Adds all the rows
                for row in rows:
                        tableRows.extend(format_row(row))
                        if self.__HTML:
                                tableRows.append(breakLine)

                # Saves the table
                if self.__HTML:
                        self.__value += "         * <pre>\n"

                self.__value += '\n'.join(tableRows) + '\n'

                if self.__HTML:
                        self.__value += "         * </pre><br>\n         * \n"

        #                                        #
        # ---------------- DIVS ---------------- #
        #                                        #

        def addListingblock(self, listingblock) -> None:
                """
                Adds a listingblock div to the cache
                :param listingblock: the listingblock div
                """
                if self.__HTML:
                        self.__value += f"         * @code\n"
                        self.__value += f"         * {listingblock.find('pre').getText(strip=True).replace('\n', "\n         * ")}\n"
                        self.__value += f"         * @endcode\n         * \n"
                else:
                        self.__value += f"    ```c\n"
                        self.__value += f"    {listingblock.find('pre').getText(strip=True).replace('\n', "\n    ")}\n"
                        self.__value += f"    ```\n         * \n"

        def addNote(self, note, listLevel: int = 0) -> None:
                """
                Adds a note div to the cache
                :param note: the note div
                :param listLevel: the level of indentation
                """
                table = note.find('table')
                if not table:
                        return

                tr = table.find('tr')
                if not tr:
                        return

                td = tr.find('td', class_='content')
                if not td:
                        return

                if listLevel != 0:
                        self.__value += '\n'

                if self.__HTML:
                        self.__value += f"         * {listLevel * "    "} @note "
                else:
                        self.__value += f"         * {listLevel * "⠀⠀⠀⠀"} @note "

                for paragraph in td.findAll('div', class_='paragraph'):
                        getHTML(paragraph, self, singleLine=True)

                self.__value += "\n         * "

                if listLevel == 0:
                        self.__value += "\n"

        def addParagraph(self, paragraph, prefix: str = '', singleLine: bool = False) -> None:
                """
                Adds a paragraph div to the cache
                :param paragraph: the paragraph div
                :param prefix: the prefix string
                :param singleLine: if the paragraph is in a single line
                """
                if not singleLine:
                        self.__value += f"         * {prefix}"

                getHTML(paragraph, self, singleLine=True)

                if self.__HTML:
                        self.__value += "<br><br>"

                if not singleLine:
                        self.__value += f"\n         * \n"

        def addTitle(self, title) -> None:
                """
                Adds a title div to the cache
                :param title: the title div
                """
                if not title:
                        return

                self.__value += "         * "

                if not self.__HTML:
                        self.__value += f"## {title.getText(strip=True).replace('\n', ' ')}\n         * \n"
                        return

                if title.find('a'):
                        self.addAnchor(title.find('a'), '', True)

                self.__value += f"<b>{title.getText(strip=True).replace('\n', ' ')}</b><hr><br>\n         * \n"

        __value: str = ""
        __URL: str = ""
        __HTML: bool = True

        @property
        def value(self) -> str:
                return self.__value

        @property
        def providers(self) -> list[str]:
                """
                Gets the providers with the current value
                """
                matches = re.findall(FIND_PROVIDERS_HTML_REGEX if self.__HTML else FIND_PROVIDERS_MD_REGEX, self.__value)
                return [
                        f"defined {parts[0].strip()} && defined {parts[1].strip()}" if ' with ' in pair else f"defined {pair.strip()}"
                        for match in matches for pair in re.split(r",\s*", match) for parts in [pair.split(' with ')]
                ]


def printDiv(div, cache: Cache, prefix: str, singleLine: bool, listLevel: int) -> None:
        """
        Caches a div
        :param div: the div to cache
        :param cache: the cache to put the div in
        :param prefix: the prefix string
        :param singleLine: if the div is in a single line
        :param listLevel: the level of indentation
        """
        if not div:
                return

        class_list = div.get('class', [])
        if 'title' in class_list:
                cache.addTitle(div)
        elif 'paragraph' in class_list:
                cache.addParagraph(div, prefix, singleLine)
        elif 'listingblock' in class_list:
                cache.addListingblock(div)
        elif 'ulist' in class_list:
                cache.addList(div, 'u', prefix, singleLine, listLevel)
        elif 'dlist' in class_list:
                cache.addList(div, 'd', prefix, singleLine, listLevel)
        elif 'sidebarblock' in class_list:
                getHTML(div.find('div', 'content'), cache, prefix)
        elif 'admonitionblock' in class_list and 'note' in class_list:
                cache.addNote(div, listLevel)
        elif 'sectionbody' in class_list:
                getHTML(div, cache, prefix, singleLine, listLevel)
        # If the div is not one of the above, we don't print it


def getHTML(element, cache: Cache, prefix: str = '', singleLine: bool = False, listLevel: int = 0) -> None:
        """
        Recursive method to get HTML elements
        :param element: the element to cache
        :param cache: the cache to put the element in
        :param prefix: the prefix string
        :param singleLine: if the element is in a single line
        :param listLevel: the level of indentation
        """
        if not element:
                return

        # If an element only contains text
        if isinstance(element, NavigableString):
                if element.strip() != "":
                        cache.addGeneric(f"{element.replace('\n', ' ')}", prefix, singleLine, listLevel)

                return

        # If not we cycle through all of its children
        for subElement in element.contents:
                match subElement.name:
                        case 'a':
                                cache.addAnchor(subElement, prefix, singleLine, listLevel)
                        case 'em':
                                cache.addEmphasized(subElement, prefix, singleLine, listLevel)
                        case 'h2':
                                cache.addTitle(subElement)
                        case 'dt':
                                cache.addDefinitionTerm(subElement, prefix, listLevel)
                        case 'dd':
                                cache.addListEntry(subElement, "dd", prefix, listLevel)
                        case 'li':
                                cache.addListEntry(subElement, "li", prefix, listLevel)
                        case 'br':
                                cache.addBreak(singleLine, listLevel)
                        case 'div':
                                printDiv(subElement, cache, prefix, singleLine, listLevel)
                        case 'sub':
                                cache.addSub(subElement)
                        case 'code':
                                cache.addCode(subElement, prefix, singleLine, listLevel)
                        case 'span':
                                cache.addSpan(subElement, prefix, singleLine, listLevel)
                        case 'strong':
                                cache.addStrong(subElement, prefix, singleLine, listLevel)
                        case 'table':
                                cache.addTable(subElement)
                        case _:
                                # If the type is not recognized, we cycle through its children
                                getHTML(subElement, cache, prefix, singleLine, listLevel)


def parseHtml(lock: Lock, url: str, html: bool) -> None:
        """
        Function to parse and extract the required information
        :param lock: the thread lock
        :param url: the url to get the html from
        :param html: if the header uses HTML or Markdown format
        """
        htmlText: str = fetchUrl(url)
        soup = BeautifulSoup(htmlText, "html.parser")

        nameHeader = soup.find('h1')
        assert nameHeader, f"Could not find name header for url '{url}'"

        content = soup.find('div', id='content')
        assert content, f"Could not find content div for url '{url}'"

        name: str = re.search(FIND_NAME_FROM_HEADER_REGEX, nameHeader.getText(strip=True)).group()
        if name in USED_NAMES:
                return

        USED_NAMES.append(name)
        cache: Cache = Cache(url, html)

        # Documentation start
        if html:
                cache.addRaw(f"        /**\n         * <b>Name</b><hr><br>\n         * \n")
        else:
                cache.addRaw(f"        /**\n         * ## Name\n         * \n")
        cache.addParagraph(nameHeader.findNext('div', class_="sectionbody"))

        # All the info is inside the content div inside divs named sect1
        for sect1 in content.findAll('div', class_="sect1"):
                sectName = sect1.find('h2').getText(strip=True)

                # Skipping useless data
                if sectName == "Document Notes" or sectName == "See Also" or sectName == "Copyright":
                        continue

                getHTML(sect1, cache)

        # Gets the providers of the current element
        providers: list[str] = cache.providers

        # Checks if it uses the default provider
        def isDefaultProvider(provider: str) -> bool:
                parts = re.split(r'\s*&&\s*', provider.replace('defined ', ''))
                return all(part.strip() in DEFAULT_PROVIDERS for part in parts)

        defaultProvider: bool = any(isDefaultProvider(provider) for provider in providers)

        # Documentation end
        cache.addRaw("        */\n        ")

        def firstLetterToLower(string: str) -> str:
                return string[0].lower() + string[1:]

        # Function / object declaration
        if name.startswith("vk"):
                cache.addRaw(f"constexpr auto {firstLetterToLower(name[2:])} = {name};\n")
        else:
                cache.addRaw(f"using {name[2:]} = {name};\n")

        with lock, open(OUTPUT_FILE, 'a', encoding='utf-8') as file:
                if not defaultProvider:
                        # Needs to be written directly since we cannot add at the cache start
                        if len(providers) > 1:
                                file.write(f"#if {' || '.join(f'({provider})' for provider in providers)}\n")
                                cache.addRaw(f"#endif // {' || '.join(f'({provider})' for provider in providers)}\n")
                        else:
                                file.write(f"#if {providers[0]}\n")
                                cache.addRaw(f"#endif // {providers[0]}\n")

                # Writes cache to file
                cache.write(file)
                file.write('\n')


def writeDocumentation(html: bool) -> None:
        """
        Writes all the documentation with the given platform style
        :param html: if the header uses HTML or Markdown format
        """
        # Split the elements into 1 chunks per thread
        chunkSize: int = math.ceil(len(VALID_ELEMENTS) / THREADS)
        chunks: list[list[str]] = [VALID_ELEMENTS[i:i + chunkSize] for i in range(0, len(VALID_ELEMENTS), chunkSize)]

        lock: Lock = threading.Lock()

        def getRegistryURL(string: str) -> str:
                return f"{VULKAN_REGISTRY}{string}.html"

        def processThread(chunk: list[str]):
                for name in chunk:
                        parseHtml(lock, getRegistryURL(name), html)

        # Start threads
        threads: list[Thread] = []
        for i in range(THREADS):
                thread = threading.Thread(target=processThread, args=(chunks[i],))
                threads.append(thread)
                thread.start()

        # Wait for all threads to complete
        for thread in threads:
                thread.join()


def getVersion() -> str:
        """
        Gets the current vulkan version
        :return: the version as a string
        """
        versionCheck = requests.get(VULKAN_VERSION_CHECK)
        versionCheck.raise_for_status()

        soup = BeautifulSoup(versionCheck.text, "html.parser")
        footer = soup.find('div', id="footer-text")
        assert footer, "Could not find version"

        return re.search(FIND_VERSION_REGEX, footer.getText(" ", strip=True)).group(1)


def fetchUrl(url: str) -> str:
        """
        Fetches the HTML content of a URL
        :param url: the url to fetch
        :return: the html content as a string
        """
        search = re.search(FIND_NAME_FROM_URL_REGEX, url)

        def createHashName() -> str:
                return str(int(hashlib.sha1(url.encode("utf-8")).hexdigest(), 16) % (10 ** 8))

        fixedUrl: str = search.group(0) if search else f"/unknown{createHashName()}.html"

        if '.' not in fixedUrl:
                fixedUrl += ".html"

        if os.path.exists(f"./.{VERSION}{fixedUrl}"):
                with open(f"./.{VERSION}{fixedUrl}", 'r', encoding='utf-8') as file:
                        return file.read()

        response = requests.get(url)
        response.raise_for_status()  # Raise an error for bad status codes

        response.encoding = "utf-8"
        with open(f"./.{VERSION}{fixedUrl}", 'w', encoding='utf-8') as file:
                file.write(response.text)

        return response.text


def getValidElements() -> list[str]:
        """
        Gets all the valid elements from vulkan registry
        :return: the valid elements as a list of strings
        """
        content: str = fetchUrl(VULKAN_REGISTRY)
        soup = BeautifulSoup(content, "html.parser")

        files = soup.find('div', id='files')
        assert files, "Could not get 'files' div"

        table = files.find('table')
        assert table, "Could not find table"

        cells = table.select('td a')
        assert cells, "Could not find element names"

        elements: list[str] = list[str]()
        for cell in cells:
                text: str = cell.getText(strip=True)

                # Skip invalid elements
                if not (text.startswith("Vk") or text.startswith("vk")):
                        continue

                elements.append(os.path.splitext(text)[0])

        return elements


def main(html: bool) -> None:
        print(f"Writing documentation for vulkan from url '{VULKAN_REGISTRY}'")
        initTime: float = time()

        if not html:
                global OUTPUT_FILE
                OUTPUT_FILE = "../vulkan++-M.hpp"

        global VERSION
        VERSION = getVersion()
        if not os.path.exists(f"./.{VERSION}/"):
                os.mkdir(f"./.{VERSION}/")

        # Writes the file start block
        with open(OUTPUT_FILE, 'w', encoding="utf-8") as file, open("./pre.txt", 'r', encoding="utf-8") as prefix:
                file.write(prefix.read())

        # Gets all valid elements
        global VALID_ELEMENTS
        VALID_ELEMENTS = getValidElements()

        # Writes the documentation
        writeDocumentation(html)

        # Writes the file end block
        with open(OUTPUT_FILE, 'a', encoding="utf-8") as file, open("./suf.txt", 'r', encoding="utf-8") as suffix:
                file.write(suffix.read())

        print(f"Documentation extracted and written to {OUTPUT_FILE} in {time() - initTime}s")


if __name__ == "__main__":
        if len(sys.argv) == 2:
                main(sys.argv[1] == 'H')
        else:
                main(True)
