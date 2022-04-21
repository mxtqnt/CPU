cmake_minimum_required(VERSION 3.22)
project(CPU)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CPU
        main.c
        README.md)
