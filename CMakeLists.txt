cmake_minimum_required(VERSION 3.5)
project(vulkan++)
set(CMAKE_CXX_STANDARD 23)

# Checking if the vulkan SDK is installed
if(NOT DEFINED ENV{VULKAN_SDK})
    message(FATAL_ERROR "Vulkan SDK not found.")
else()
    message(STATUS "Found Vulkan SDK.")
endif()

add_library(${PROJECT_NAME} STATIC vulkan++.cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE VULKANPP_INCLUDE_VULKAN)
target_compile_definitions(${PROJECT_NAME} PRIVATE VULKANPP_ENABLE_CONSTEXPR)
target_compile_definitions(${PROJECT_NAME} PRIVATE VULKANPP_FORCE_INLINE)

# Linking Vulkan
target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VULKAN_SDK}/Include)