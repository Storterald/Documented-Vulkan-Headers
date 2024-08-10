cmake_minimum_required(VERSION 3.5)

# Project
project(vulkan++ CXX)

# Embed shaders
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp
        WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E env python generate.py ${VULKAN_WITH_DOC_FLAGS}
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp
        DEPENDS generate.py
)
add_custom_target(pre-build DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp)

# Executable just to run generate.py
add_executable(${PROJECT_NAME} dummy.cpp ../vulkan++.hpp)

# Adding the python script as a dependency
add_dependencies(${PROJECT_NAME} pre-build)