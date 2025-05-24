cmake_minimum_required(VERSION 3.10)

project(ex6 C)

set(CMAKE_C_STANDARD 99)

# Automatically include all .c files in this directory
file(GLOB SOURCES "*.c")
add_executable(ex6 ${SOURCES})

set(CMAKE_BUILD_TYPE Debug)