cmake_minimum_required(VERSION 3.5)
# Project
project(vulkan++ CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Checking if the vulkan SDK is installed
if(NOT DEFINED ENV{VULKAN_SDK})
    message(FATAL_ERROR "Vulkan SDK not found.")
else()
    message(STATUS "Found Vulkan SDK.")
endif()

# Embed shaders
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp
        WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E env python generate.py
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp
        DEPENDS generate.py
)
add_custom_target(pre-build DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/pre-build.stamp)

# Executable just to run generate.py
add_executable(${PROJECT_NAME} main.cpp ../vulkan++.hpp)

# Adding the python script as a dependency
add_dependencies(${PROJECT_NAME} pre-build)

# Linking Vulkan
target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VULKAN_SDK}/Include)
target_compile_definitions(${PROJECT_NAME} PRIVATE VULKANPP_INCLUDE_VULKAN)