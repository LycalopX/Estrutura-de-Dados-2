cmake_minimum_required(VERSION 3.10)

project(main C)

set(CMAKE_C_STANDARD 99)

# Automatically include all .c files in this directory
file(GLOB SOURCES "*.c")
add_executable(main ${SOURCES})

set(CMAKE_BUILD_TYPE Debug)