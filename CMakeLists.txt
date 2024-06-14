cmake_minimum_required(VERSION 3.5)
project(vulkan++)
set(CMAKE_CXX_STANDARD 23)

add_library(${PROJECT_NAME} STATIC vulkan++.cpp)

target_compile_definitions(${PROJECT_NAME} PUBLIC VULKANPP_INCLUDE_VULKAN)
target_compile_definitions(${PROJECT_NAME} PUBLIC VULKANPP_ENABLE_CONSTEXPR)
target_include_directories(${PROJECT_NAME} PUBLIC $ENV{VULKAN_SDK}/Include)