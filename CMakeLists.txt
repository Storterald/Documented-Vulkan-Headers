cmake_minimum_required(VERSION 3.5)

# Project
project(VULKAN_WITH_DOC CXX)

# Directory with python script
set(BIN_DIR ${CMAKE_HOME_DIRECTORY}/bin)

# Install by default
option(VULKAN_WITH_DOC_INSTALL "Generate installation target" ON)

# Embed shaders
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp
        COMMAND ${CMAKE_COMMAND} -E echo "Generating header with flags: '${VULKAN_WITH_DOC_FLAGS}'"
        COMMAND ${CMAKE_COMMAND} -E env python generate.py ${VULKAN_WITH_DOC_FLAGS}
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp
        WORKING_DIRECTORY ${BIN_DIR}
)
add_custom_target(pre-build DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp)

# Move the headers in a include directory
if (VULKAN_WITH_DOC_INSTALL)
        install(DIRECTORY include/vulkan DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN vulkan++.hpp)
endif ()

# Executable just to run generate.py
add_library(VULKAN_WITH_DOC OBJECT ${BIN_DIR}/dummy.cpp)

# Adding the python script as a dependency
add_dependencies(VULKAN_WITH_DOC pre-build)