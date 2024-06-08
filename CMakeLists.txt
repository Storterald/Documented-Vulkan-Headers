cmake_minimum_required(VERSION 3.5)
project(vulkan++)
set(CMAKE_CXX_STANDARD 23)

add_library(${PROJECT_NAME} STATIC vulkan++.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC $ENV{VULKAN_SDK}/Include)