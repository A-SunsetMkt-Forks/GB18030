cmake_minimum_required(VERSION 3.16)
project(GB18030 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    GbString.hpp
    GbString.cpp
    GbMapping.cpp
    main.cpp
)

add_executable(GB18030 ${PROJECT_SOURCES})