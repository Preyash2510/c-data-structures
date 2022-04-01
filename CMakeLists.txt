cmake_minimum_required(VERSION 3.16)  # CMake version check
project(c-data-structures)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 23)              # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES test.c list/list.c list/list.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(c-data-structures ${SOURCE_FILES})