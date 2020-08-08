cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(UTILS
        utils/utils.h
        utils/utils.cpp)

set(UTILITY
        utility/main.cpp
        utility/coding_buffers.h
        utility/utility.h
        utility/utility.cpp)

add_subdirectory(library)

add_executable(huffman config.h ${UTILITY} ${UTILS})

target_link_libraries(huffman huflib)