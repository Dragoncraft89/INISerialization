cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -Wno-unused-function")

project(tests)

add_executable(tests ../INISerializer.cpp UnitTest++.cpp DeserializationTest.cpp SerializationTest.cpp MalformedTests.cpp)
TARGET_INCLUDE_DIRECTORIES(tests PRIVATE ../include)
