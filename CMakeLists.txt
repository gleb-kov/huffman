cmake_minimum_required(VERSION 3.16)
project(huffman)

set(CMAKE_CXX_STANDARD 17)

set(GTEST_SRC
        ${PROJECT_SOURCE_DIR}/gtest/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/gtest/gtest.h
        ${PROJECT_SOURCE_DIR}/gtest/gtest_main.cc)

add_library(huflib STATIC
        lib/bitcode.h
        lib/bitcode.cpp
        lib/encode_deque.h
        lib/encode_deque.cpp
        lib/coding.h
        lib/coding.cpp)

add_executable(huffman main.cpp utility/defs.h utility/compress.cpp utility/decompress.cpp utils/file.h utils/types.h utils/defs.h utils/utils.cpp)

target_link_libraries(huffman huflib)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb -std=c++17 -pedantic -O2 -flto")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -fsanitize=address,undefined,leak")
endif()