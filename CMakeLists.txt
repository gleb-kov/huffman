cmake_minimum_required(VERSION 3.16)
project(huffman)

set(CMAKE_CXX_STANDARD 17)

set(GTEST_SRC
        ${PROJECT_SOURCE_DIR}/gtest/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/gtest/gtest.h
        ${PROJECT_SOURCE_DIR}/gtest/gtest_main.cc)

include_directories(.)

add_subdirectory(src)
add_subdirectory(tests)