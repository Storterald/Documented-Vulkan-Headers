import re
import os
import sys
import math
import html
import hashlib
import requests
from time import time
from bs4 import BeautifulSoup, NavigableString
from concurrent.futures import ThreadPoolExecutor

# Constants
VULKAN_DOCUMENTATION: str = "https://vulkan.lunarg.com/doc/view/latest/windows/apispec.html"
VULKAN_REGISTRY: str = "https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/"
VULKAN_VERSION_CHECK: str = "https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VK_API_VERSION.html"
OUTPUT_FILE: str = "../vulkan++.hpp"
THREADS: int = 16
HEADER_REGEX: str = r" {9}\* <b>[A-Za-z0-9 ()]+<\/b><hr><br>\n"
EMPTY_LINE_REGEX: str = r" {9}\* \n"
CHAR_FIX_MAP: dict[str, str] = {
        "\\rfloor": '⌋',
        "\\lfloor": '⌊',
        "\\times": '×',
        "\\(": '',
        "\\)": ''
}
PROVIDER_DEFINES: dict[str, str] = {
        # "vulkan_win32.h" VK_USE_PLATFORM_WIN32_KHR
        "vkAcquireFullScreenExclusiveModeEXT": "VK_USE_PLATFORM_WIN32_KHR",
        "vkGetFenceWin32HandleKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "vkGetSemaphoreWin32HandleKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "vkGetDeviceGroupSurfacePresentModes2EXT": "VK_USE_PLATFORM_WIN32_KHR",
        "vkCreateWin32SurfaceKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "vkGetPhysicalDeviceSurfacePresentModes2EXT": "VK_USE_PLATFORM_WIN32_KHR",
        "vkReleaseFullScreenExclusiveModeEXT": "VK_USE_PLATFORM_WIN32_KHR",
        "vkGetMemoryWin32HandleKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "vkGetMemoryWin32HandleNV": "VK_USE_PLATFORM_WIN32_KHR",
        "VkImportMemoryWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "vkImportFenceWin32HandleKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "vkGetMemoryWin32HandlePropertiesKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "vkImportSemaphoreWin32HandleKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "vkGetPhysicalDeviceWin32PresentationSupportKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkExportMemoryWin32HandleInfoNV": "VK_USE_PLATFORM_WIN32_KHR",
        "VkExportMemoryWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkImportMemoryWin32HandleInfoNV": "VK_USE_PLATFORM_WIN32_KHR",
        "VkExportSemaphoreWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkImportSemaphoreWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkFenceGetWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkWin32KeyedMutexAcquireReleaseInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkWin32KeyedMutexAcquireReleaseInfoNV": "VK_USE_PLATFORM_WIN32_KHR",
        "VkMemoryGetWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkWin32SurfaceCreateInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkSemaphoreGetWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkD3D12FenceSubmitInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkSurfaceCapabilitiesFullScreenExclusiveEXT": "VK_USE_PLATFORM_WIN32_KHR",
        "VkMemoryWin32HandlePropertiesKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkSurfaceFullScreenExclusiveInfoEXT": "VK_USE_PLATFORM_WIN32_KHR",
        "VkExportFenceWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkSurfaceFullScreenExclusiveWin32InfoEXT": "VK_USE_PLATFORM_WIN32_KHR",
        "VkImportFenceWin32HandleInfoKHR": "VK_USE_PLATFORM_WIN32_KHR",
        "VkFullScreenExclusiveEXT": "VK_USE_PLATFORM_WIN32_KHR",
        "VkWin32SurfaceCreateFlagsKHR": "VK_USE_PLATFORM_WIN32_KHR",

        # "vulkan_xlib_xrandr.h" VK_USE_PLATFORM_XLIB_XRANDR_EXT
        "vkAcquireXlibDisplayEXT": "VK_USE_PLATFORM_XLIB_XRANDR_EXT",
        "vkGetRandROutputDisplayEXT": "VK_USE_PLATFORM_XLIB_XRANDR_EXT",

        # "vulkan_android.h" VK_USE_PLATFORM_ANDROID_KHR
        "vkGetAndroidHardwareBufferPropertiesANDROID": "VK_USE_PLATFORM_ANDROID_KHR",
        "vkGetMemoryAndroidHardwareBufferANDROID": "VK_USE_PLATFORM_ANDROID_KHR",
        "vkCreateAndroidSurfaceKHR": "VK_USE_PLATFORM_ANDROID_KHR",
        "VkAndroidHardwareBufferFormatPropertiesANDROID": "VK_USE_PLATFORM_ANDROID_KHR",
        "VkAndroidHardwareBufferPropertiesANDROID": "VK_USE_PLATFORM_ANDROID_KHR",
        "VkAndroidHardwareBufferUsageANDROID": "VK_USE_PLATFORM_ANDROID_KHR",
        "VkAndroidSurfaceCreateInfoKHR": "VK_USE_PLATFORM_ANDROID_KHR",
        "VkExternalFormatANDROID": "VK_USE_PLATFORM_ANDROID_KHR",
        "VkMemoryGetAndroidHardwareBufferInfoANDROID": "VK_USE_PLATFORM_ANDROID_KHR",
        "VkImportAndroidHardwareBufferInfoANDROID": "VK_USE_PLATFORM_ANDROID_KHR",

        # "vulkan_ggp.h" VK_USE_PLATFORM_GGP
        "vkCreateStreamDescriptorSurfaceGGP": "VK_USE_PLATFORM_GGP",
        "VkStreamDescriptorSurfaceCreateInfoGGP": "VK_USE_PLATFORM_GGP",
        "VkPresentFrameTokenGGP": "VK_USE_PLATFORM_GGP",

        # "vulkan_ios.h" VK_USE_PLATFORM_IOS_MVK
        "vkCreateIOSSurfaceMVK": "VK_USE_PLATFORM_IOS_MVK",
        "VkIOSSurfaceCreateInfoMVK": "VK_USE_PLATFORM_IOS_MVK",

        # "vulkan_fuchsia.h" VK_USE_PLATFORM_FUCHSIA
        "vkCreateImagePipeSurfaceFUCHSIA": "VK_USE_PLATFORM_FUCHSIA",
        "VkImagePipeSurfaceCreateInfoFUCHSIA": "VK_USE_PLATFORM_FUCHSIA",

        # "vulkan_vi.h" VK_USE_PLATFORM_VI_NN
        "vkCreateViSurfaceNN": "VK_USE_PLATFORM_VI_NN",
        "VkViSurfaceCreateInfoNN": "VK_USE_PLATFORM_VI_NN",

        # "vulkan_wayland.h" VK_USE_PLATFORM_WAYLAND_KHR
        "vkCreateWaylandSurfaceKHR": "VK_USE_PLATFORM_WAYLAND_KHR",
        "vkGetPhysicalDeviceWaylandPresentationSupportKHR": "VK_USE_PLATFORM_WAYLAND_KHR",
        "VkWaylandSurfaceCreateInfoKHR": "VK_USE_PLATFORM_WAYLAND_KHR",

        # "vulkan_macos.h" VK_USE_PLATFORM_MACOS_MVK
        "vkCreateMacOSSurfaceMVK": "VK_USE_PLATFORM_MACOS_MVK",
        "VkMacOSSurfaceCreateInfoMVK": "VK_USE_PLATFORM_MACOS_MVK",

        # "vulkan_xcb.h" VK_USE_PLATFORM_XCB_KHR
        "vkCreateXcbSurfaceKHR": "VK_USE_PLATFORM_XCB_KHR",
        "vkGetPhysicalDeviceXcbPresentationSupportKHR": "VK_USE_PLATFORM_XCB_KHR",
        "VkXcbSurfaceCreateInfoKHR": "VK_USE_PLATFORM_XCB_KHR",

        # "vulkan_metal.h" VK_USE_PLATFORM_METAL_EXT
        "vkCreateMetalSurfaceEXT": "VK_USE_PLATFORM_METAL_EXT",
        "VkMetalSurfaceCreateInfoEXT": "VK_USE_PLATFORM_METAL_EXT",

        # "vulkan_xlib.h" VK_USE_PLATFORM_XLIB_KHR
        "vkCreateXlibSurfaceKHR": "VK_USE_PLATFORM_XLIB_KHR",
        "vkGetPhysicalDeviceXlibPresentationSupportKHR": "VK_USE_PLATFORM_XLIB_KHR",
        "VkXlibSurfaceCreateInfoKHR": "VK_USE_PLATFORM_XLIB_KHR",
}

# Global variables
VALID_ELEMENTS: list[str] = list[str]()
VERSION: str = ""


def firstLetterToLower(string: str) -> str:
        """
        Lowercases the first letter of a string
        :param string: the string to change
        :return: the new string
        """
        return string[0].lower() + string[1:]


def fixName(string: str) -> str:
        """
        Fixes the header name
        :param string: the header text
        :return: the fixed header text
        """
        return re.sub(r"\(\d+\)", '', string).strip()


def getFragmentIdentifierURL(string: str) -> str:
        """
        Adds prefix and suffix to a fragment identifier
        :param string: the element name
        :return: the khronos url
        """
        return f"{VULKAN_REGISTRY}{string}.html"


class Cache:
        def __init__(self, platform: str):
                self.__platform = platform  # TODO vs and vscode support

        def __addGeneric(self, string: str, prefix: str, singleLine: bool, listLevel: int):
                """
                Generic method to add a string to the documentation
                :param string: the string to add
                :param prefix: the prefix string
                :param singleLine: if the element is in a single line
                :param listLevel: the level of indentation
                """
                if not singleLine:
                        self.__value += f"         * {listLevel * "    "}"

                self.__value += prefix + string
                if not singleLine:
                        self.__value += '\n'

        def write(self, file):
                """
                Writes the cached value to the given file
                :param file: the already open file to write to
                """
                string = self.__value

                # Fix math
                for old, new in CHAR_FIX_MAP.items():
                        string = string.replace(old, new)
                string = re.sub(r"(?<=[\s,.=])([a-zA-Z])_([a-zA-Z]+)(?=[\s,.=])", r"\1<sub>\2</sub>", string)

                # Removes empty headers
                string = re.sub(r"(" + HEADER_REGEX + EMPTY_LINE_REGEX + r")*(" + HEADER_REGEX + r")", r"\2", string)

                # Removes empty headers, empty lines and breaks before the end of the documentation
                string = re.sub(
                        r"(((" + EMPTY_LINE_REGEX + r")*" + HEADER_REGEX + r")|(((<br>)+)(?=\n)))(\n?)(" + EMPTY_LINE_REGEX + r")*(?=( {8}\*\/))",
                        r"\7", string)

                # Remove <br> when not needed
                string = re.sub(r"(<br>)+\n(" + EMPTY_LINE_REGEX + r")*( {9}\* (@|(<dl>)|(<pre>)))", r"\n\2\3", string)
                string = re.sub(r"(<br>){2}(\n(" + EMPTY_LINE_REGEX + r")* {9}\* <ul>)", r"\2", string)

                # Remove extra spaces
                string = re.sub(r"( {9}\* ( {4})*)( )*", r"\1", string)
                string = re.sub(r"(?<=[^ \n\|]) {2}(?=[^ \n\|])", ' ', string)

                # Writes the fixed cache
                file.write(string)

        #                                        #
        # -------------- ELEMENTS -------------- #
        #                                        #

        def addRaw(self, string: str):
                """
                Adds a string to the cache
                :param string: the string to add
                """
                self.__value += string

        def addSub(self, sub):
                """
                Adds a sub element to the cache
                :param sub: the sub element
                """
                tempCache = Cache(self.__platform)
                getHTML(sub, tempCache, singleLine=True)
                self.__value += "<sub>" + tempCache.__value + "</sub>"

        def addEmphasized(self, emphasized, prefix: str, singleLine: bool, listLevel: int):
                """
                Adds an emphasized element to the cache
                :param emphasized: the emphasized element
                :param prefix: the prefix string
                :param singleLine: if the emphasized element is in a single line
                :param listLevel: the level of indentation
                """
                if not emphasized:
                        return

                text: str = f"<i>{emphasized.getText(strip=True).replace('\n', ' ')}</i>"
                self.__addGeneric(text, prefix, singleLine, listLevel)

        def addDefinitionTerm(self, definitionTerm, prefix: str, listLevel: int):
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

                self.__value += f"         * {listLevel * "    "}{prefix}<dt>{text}\n"

        def addDefinitionDescription(self, definitionDescription, prefix: str, listLevel: int):
                """
                Adds a definition description element to the cache
                :param definitionDescription:
                :param prefix: the prefix string
                :param listLevel: the level of indentation
                """
                self.__value += f"         * {listLevel * "    "}{prefix}<dd>"
                getHTML(definitionDescription, self, singleLine=True, listLevel=listLevel + 1)
                self.__value += '\n'

        def addListEntry(self, listEntry, prefix: str, listLevel: int):
                """
                Adds a list entry element to the cache
                :param listEntry: the list entry element
                :param prefix: the prefix string
                :param listLevel: the level of indentation
                """
                self.__value += f"         * {listLevel * "    "}{prefix}<li>"
                getHTML(listEntry, self, singleLine=True, listLevel=listLevel + 1)
                self.__value += '\n'

        def addBreak(self, singleLine: bool, listLevel: int):
                """
                Adds a break element to the cache
                :param singleLine: if the break is in a single line
                :param listLevel: the level of indentation
                """
                self.__value += "<br>\n"
                # A break must always create a new line
                if singleLine:
                        self.__value += f"         * {listLevel * "    "}"

        def addCode(self, code, prefix: str, singleLine: bool, listLevel: int):
                """
                Adds a code element to the cache
                :param code: the code element
                :param prefix: the prefix string
                :param singleLine: if the code is in a single line
                :param listLevel: the level of indentation
                """
                if not code:
                        return

                text: str = f"<i><b>{code.getText(strip=True).replace('\n', ' ')}</b></i>"
                self.__addGeneric(text, prefix, singleLine, listLevel)

        def addStrong(self, strong, prefix: str, singleLine: bool, listLevel: int):
                """
                Adds a strong element to the cache
                :param strong: the strong element
                :param prefix: the prefix string
                :param singleLine: if the strong element is in a single line
                :param listLevel: the level of indentation
                """
                if not strong:
                        return

                text: str = f" <b>{strong.getText(strip=True).replace('\n', ' ')}</b>"
                self.__addGeneric(text, prefix, singleLine, listLevel)

        def addSpan(self, span, prefix: str, singleLine: bool, listLevel: int):
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
                        tempCache = Cache(self.__platform)
                        getHTML(span, tempCache, singleLine=True)
                        text = tempCache.__value

                if text.strip() == "":
                        return

                if not singleLine:
                        self.__value += f"         * {listLevel * "    "}"

                self.__value += f"{prefix}{text.replace('\n', ' ')}"

        def addList(self, list, prefix: str, listType: str, singleLine: bool, listLevel: int):
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

                self.__value += f"         * {listLevel * "    "}{prefix}<{listType}l>\n"

                getHTML(list, self, prefix, listLevel=listLevel + 1)

                self.__value += f"         * {listLevel * "    "}{prefix}</{listType}l>"

                if singleLine:
                        return

                self.__value += "<br>\n"
                if not prefix:
                        self.__value += "         * \n"

        def addAnchor(self, anchor, prefix: str, singleLine: bool, listLevel: int):
                """
                Adds an anchor element to the cache
                :param anchor: the anchor element
                :param prefix: the prefix string
                :param singleLine: if the anchor is in a single line
                :param listLevel: the level of indentation
                """
                if anchor.has_attr('class'):
                        return

                if not singleLine:
                        self.__value += f"         * {listLevel * "    "}"

                # We keep the href only if it's a valid link
                if anchor.has_attr('href'):
                        content = anchor['href'].strip()
                        if content.startswith("http"):
                                text: str = str(anchor).replace('\n', ' ').replace("<code>", "<i><b>").replace(
                                        "</code>", "</b></i>")
                                self.__value += f"{prefix} {text}"
                        elif content.startswith("#"):
                                text = anchor.getText(strip=True)
                                self.__value += f"{prefix} <a href=\"{getFragmentIdentifierURL(text)}\">{text}</a>"
                else:
                        self.__value += f"{prefix}{anchor.getText(strip=True)}"

                if not singleLine:
                        self.__value += '\n'

        def addTable(self, table):
                """
                Adds a table element to the cache
                :param table: the table element
                """
                if not table:
                        return

                # Removes whitespace and breaks, adds spaces when needed
                def fixHTML(item) -> str:
                        # Replace <br> tags with newline characters
                        for br in item.findAll("br"):
                                br.replace_with('\n')

                        # Get text content without stripping newlines
                        text = ''.join(str(content) for content in item.contents)

                        # Remove html, extra '\n' and ' '
                        text = re.sub(r"\s*\n\s*", '\n', text.strip())
                        text = re.sub(r"<([^<>])+>", '', text)
                        text = re.sub(r"( )+", ' ', text)

                        # Unescape HTML entities
                        text = html.unescape(text)

                        return text

                # Extract headers and rows
                headElements = table.find('thead').find('tr').findAll('th') if table.find('thead') else \
                table.findAll('tr')[0].findAll('td')
                headers = [fixHTML(cell) for cell in headElements]
                rows = [[fixHTML(cell) for cell in tr.findAll(['th', 'td'])] for tr in table.findAll('tr')[1:]]

                # Ensure each row has the correct number of columns
                for row in rows:
                        while len(row) < len(headers):
                                row.append('')

                # Determine the width of each column
                columns = [headers] + rows
                col_widths = [max(len(line) for cell in col for line in cell.split('\n')) + 2 for col in zip(*columns)]

                # Print the table with proper formatting
                def format_row(row):
                        formatted_lines = [cell.split('\n') for cell in row]
                        max_lines = max(len(lines) for lines in formatted_lines)

                        formatted_row = []
                        for line_index in range(max_lines):
                                formatted_cells = []
                                for cell_index, lines in enumerate(formatted_lines):
                                        line = lines[line_index] if line_index < len(lines) else ''
                                        formatted_cells.append(f"{line:<{col_widths[cell_index] - 2}}")
                                formatted_row.append(f"         * |  {'  |  '.join(formatted_cells)}  |<br>")
                        return formatted_row

                breakLine = "         * " + '-' * (sum(col_widths) + 3 * len(col_widths) + 1) + "<br>"

                # The whole table, initialized with the headers
                formatted_table = [
                        breakLine, *format_row(headers), breakLine
                ]

                # Adds all the rows
                for row in rows:
                        formatted_table.extend(format_row(row))
                        formatted_table.append(breakLine)

                # Saves the table
                self.__value += "         * <pre>\n"
                self.__value += '\n'.join(formatted_table) + '\n'
                self.__value += "         * </pre><br>\n         * \n"

        #                                        #
        # ---------------- DIVS ---------------- #
        #                                        #

        def addTitle(self, title):
                """
                Adds a title div to the cache
                :param title: the title div
                """
                if not title:
                        return

                self.__value += f"         * <b>{title.getText(strip=True).replace('\n', ' ')}</b><hr><br>\n         * \n"

        def addListingblock(self, listingblock):
                """
                Adds a listingblock div to the cache
                :param listingblock: the listingblock div
                """
                self.__value += f"         * @code\n"
                self.__value += f"         * {listingblock.find('pre').getText(strip=True).replace('\n', "\n         * ")}\n"
                self.__value += f"         * @endcode\n         * \n"

        def addParagraph(self, paragraph, prefix: str, listLevel: int):
                """
                Adds a paragraph div to the cache
                :param paragraph: the paragraph div
                :param prefix: the prefix string
                :param listLevel: the level of indentation
                """
                self.__value += f"         * {listLevel * "    "}{prefix}"
                getHTML(paragraph, self, prefix, True, listLevel)
                self.__value += f"<br><br>\n         * \n"

        def addNote(self, note, listLevel: int):
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

                self.__value += f"         * {listLevel * "    "} @note "
                for paragraph in td.findAll('div', class_='paragraph'):
                        getHTML(paragraph, self, singleLine=True)

                if listLevel != 0:
                        return

                self.__value += "\n         * \n"

        __value = ""


def printDiv(div, cache: Cache, prefix: str, singleLine: bool, listLevel: int):
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
                cache.addParagraph(div, prefix, listLevel)
        elif 'listingblock' in class_list:
                cache.addListingblock(div)
        elif 'ulist' in class_list:
                cache.addList(div, prefix, 'u', singleLine, listLevel)
        elif 'dlist' in class_list:
                cache.addList(div, prefix, 'd', singleLine, listLevel)
        elif 'sidebarblock' in class_list:
                getHTML(div.find('div', 'content'), cache, prefix)
        elif 'admonitionblock' in class_list and 'note' in class_list:
                cache.addNote(div, listLevel)
        # If the div is not one of the above, we don't print it


def getHTML(element, cache: Cache, prefix: str = '', singleLine: bool = False, listLevel: int = 0):
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
                        cache.addRaw((
                                             '' if singleLine else f"         * {listLevel * "    "}") + f"{prefix}{element.replace('\n', ' ')}" + (
                                             '' if singleLine else '\n'))

                return

        # If not we cycle through all of its children
        for subElement in element.contents:
                match subElement.name:
                        case 'a':
                                cache.addAnchor(subElement, prefix, singleLine, listLevel)
                        case 'em':
                                cache.addEmphasized(subElement, prefix, singleLine, listLevel)
                        case 'h4':
                                cache.addTitle(subElement)
                        case 'dt':
                                cache.addDefinitionTerm(subElement, prefix, listLevel)
                        case 'dd':
                                cache.addDefinitionDescription(subElement, prefix, listLevel)
                        case 'li':
                                cache.addListEntry(subElement, prefix, listLevel)
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


def processSection2(sect2, function: bool, platform: str):
        """
        Process a sect2
        :param sect2: the sect2 to process
        :param function: if the sect2 is a function
        :param platform: the IDE documentation format
        """
        h3 = sect2.find('h3')
        if not h3:
                return

        name: str = fixName(h3.get_text(strip=True))
        provider: str | None = PROVIDER_DEFINES.get(name, "VULKAN")

        cache = Cache(platform)

        # Add a preprocessor to check if the required file is included
        if provider != "VULKAN":
                cache.addRaw(f"#ifdef {provider}\n")

        cache.addRaw("        /**\n")

        # Prints every sect and formats it to valid documentation
        for sect3 in sect2.findAll('div', class_='sect3'):
                sectName = sect3.find('h4').getText(strip=True)

                # Skipping useless data
                if sectName == "Document Notes" or sectName == "See Also":
                        continue

                getHTML(sect3, cache)

        # Documentation end and commenting invalid elements
        if name not in VALID_ELEMENTS:
                cache.addRaw("        */\n        // ")
        else:
                cache.addRaw("        */\n        ")

        # Function / object declaration
        if function:
                cache.addRaw(f"constexpr auto {firstLetterToLower(name[2:])} = {name};\n")
        else:
                cache.addRaw(f"using {name[2:]} = {name};\n")

        # Closing the preprocessor check
        if provider != "VULKAN":
                cache.addRaw("#endif\n")

        cache.addRaw('\n')

        with open(OUTPUT_FILE, 'a', encoding='utf-8') as file:
                # Writes cache to file
                cache.write(file)


def processSection(section, function: bool, platform: str):
        """
        Processes a section
        :param section: the section to process
        :param function: if the section is a function section
        :param platform: the IDE documentation format
        """
        sectionbody = section.find_next('div', class_='sectionbody')
        if not sectionbody:
                return

        sections = sectionbody.findAll('div', class_='sect2')
        if not sections:
                return

        # Split the elements into 1 chunks per thread
        chunkSize = math.ceil(len(sections) / THREADS)
        chunks = [sections[i:i + chunkSize] for i in range(0, len(sections), chunkSize)]

        def processChunk(chunk):
                for element in chunk:
                        processSection2(element, function, platform)

        # Create a ThreadPoolExecutor to manage the threads
        with ThreadPoolExecutor(max_workers=THREADS) as executor:
                # Submit the chunks to be processed in parallel
                futures = [executor.submit(processChunk, chunk) for chunk in chunks]

                # Wait for all threads to complete
                for future in futures:
                        future.result()  # This will re-raise any exceptions that occurred


def parseHtml(content: str, platform: str):
        """
        Function to parse and extract the required information
        :param content: the html content
        :param platform: the IDE documentation format
        """
        soup = BeautifulSoup(content, "html.parser")

        # Extract and write functions
        functionSect = soup.find('h2', id='protos')
        if functionSect:
                print("Found 'Vulkan Commands' section")
                processSection(functionSect, True, platform)

        # Extract and write handles
        handlesSect = soup.find('h2', id='handles')
        if handlesSect:
                print("Found 'Object Handles' section")
                processSection(handlesSect, False, platform)

        # Extract and write structs
        structsSect = soup.find('h2', id='structs')
        if structsSect:
                print("Found 'Structures' section")
                processSection(structsSect, False, platform)

        # Extract and write enums
        enumsSect = soup.find('h2', id='enums')
        if enumsSect:
                print("Found 'Enumerations' section")
                processSection(enumsSect, False, platform)

        # Extract and write scalar types
        scalarTypesSect = soup.find('h2', id='basetypes')
        if scalarTypesSect:
                print("Found 'Scalar Types' section")
                processSection(scalarTypesSect, False, platform)

        # Extract and write flags
        flagsSect = soup.find('h2', id='flags')
        if flagsSect:
                print("Found 'Flags' section")
                processSection(flagsSect, False, platform)


def getVersion() -> str:
        """
        Gets the current vulkan version
        :return: the version as a string
        """
        global VERSION
        if VERSION != "":
                return VERSION

        versionCheck = requests.get(VULKAN_VERSION_CHECK)
        versionCheck.raise_for_status()

        soup = BeautifulSoup(versionCheck.text, "html.parser")
        footer = soup.find('div', id="footer-text")
        if not footer:
                raise "Could not find version"

        return re.search(r"(?<=Version )([\d.]+)", footer.getText(" ", strip=True)).group(1)


def fetchUrl(url: str) -> str:
        """
        Fetches the HTML content of a URL
        :param url: the url to fetch
        :return: the html content as a string
        """
        search = re.search(r"\/(?:.(?!\/))+$", url)

        fixedUrl: str = search.group(
                0) if search else f"/unknown{int(hashlib.sha1(url.encode("utf-8")).hexdigest(), 16) % (10 ** 8)}.html"

        if '.' not in fixedUrl:
                fixedUrl += ".html"

        if os.path.exists(f"./.{VERSION}{fixedUrl}"):
                with open(f"./.{VERSION}{fixedUrl}", 'r') as file:
                        return file.read()

        response = requests.get(url)
        response.raise_for_status()  # Raise an error for bad status codes
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
        assert files

        table = files.find('table')
        assert table

        cells = table.select('td a')
        assert cells

        elements: list[str] = list[str]()
        for cell in cells:
                elements.append(os.path.splitext(cell.getText(strip=True))[0])

        return elements


def main(platform: str):
        initTime: float = time()

        global VERSION
        VERSION = getVersion()
        if not os.path.exists(f"./.{VERSION}/"):
                os.mkdir(f"./.{VERSION}/")

        # Prepares the file
        with open(OUTPUT_FILE, 'w') as file:
                with open("./pre.txt", 'r') as prefix:
                        file.write(prefix.read())

        content: str = fetchUrl(VULKAN_DOCUMENTATION)

        global VALID_ELEMENTS
        VALID_ELEMENTS = getValidElements()

        parseHtml(content, platform)

        with open(OUTPUT_FILE, 'a') as file:
                with open("./suf.txt", 'r') as suffix:
                        file.write(suffix.read())

        print(f"Documentation extracted and written to {OUTPUT_FILE} in {time() - initTime}s")


if __name__ == "__main__":
        main('clion' if len(sys.argv) < 2 else sys.argv[1])
