cmake_minimum_required(VERSION 3.5)

# Project
project(vulkan++ CXX)

# Directory with python script
set(BIN_DIR ${CMAKE_HOME_DIRECTORY}/bin)

# Embed shaders
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp
        COMMAND ${CMAKE_COMMAND} -E echo "Generating header with flags: '${VULKAN_WITH_DOC_FLAGS}'"
        COMMAND ${CMAKE_COMMAND} -E env python generate.py ${VULKAN_WITH_DOC_FLAGS}
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp
        WORKING_DIRECTORY ${BIN_DIR}
)
add_custom_target(pre-build DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp)

# Executable just to run generate.py
add_executable(${PROJECT_NAME} ${BIN_DIR}/dummy.cpp vulkan++.hpp)

# Adding the python script as a dependency
add_dependencies(${PROJECT_NAME} pre-build)