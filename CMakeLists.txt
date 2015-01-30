cmake_minimum_required(VERSION 2.8.4)
project(task01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    bintree.c
    bintree.h
    treetest.c)

add_executable(task01 ${SOURCE_FILES})