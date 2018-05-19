cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

if(BUILD_TESTS)
    message("Building Tests")
    add_subdirectory(tests)
endif()

project(INISerialization)

add_library(INISerialization INISerializer.cpp)
TARGET_INCLUDE_DIRECTORIES(INISerialization PRIVATE include)
