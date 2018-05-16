cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

project(INISerialization)

add_library(INISerialization INISerializer.cpp)
TARGET_INCLUDE_DIRECTORIES(INISerialization PRIVATE include)
