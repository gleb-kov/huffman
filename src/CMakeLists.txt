cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(SRC_UTILS
        ${SRC_DIR}/utils/utils.h
        ${SRC_DIR}/utils/utils.cpp)

set(SRC_UTILITY
        ${SRC_DIR}/library/coding.h
        ${SRC_DIR}/library/coding.cpp

        ${SRC_DIR}/utility/main.cpp
        ${SRC_DIR}/utility/coding_buffers.h
        ${SRC_DIR}/utility/utility.h
        ${SRC_DIR}/utility/utility.cpp)

add_subdirectory(library)

add_executable(huffman config.h ${SRC_UTILITY} ${SRC_UTILS})
target_link_libraries(huffman huflib stdc++fs)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -pedantic -O2")
    set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -ggdb -fsanitize=address,undefined,leak")
endif()
