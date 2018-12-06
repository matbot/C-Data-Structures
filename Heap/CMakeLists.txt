cmake_minimum_required(VERSION 3.8)
project(Heap_C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Heap_C.h Heap_C.c)
add_executable(Heap_C ${SOURCE_FILES})