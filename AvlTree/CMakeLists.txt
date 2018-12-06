cmake_minimum_required(VERSION 3.8)
project(AVL_Tree_C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c  avlTree.h avlTree.c)
add_executable(AVL_Tree_C ${SOURCE_FILES} main.c avlTree.h  avlTree.c)
