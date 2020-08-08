cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(UTILS
        utils/utils.h
        utils/utils.cpp)

add_subdirectory(library)

add_executable(huffman utility/main.cpp utility/utility.h utility/utility.cpp ${UTILS} config.h)

target_link_libraries(huffman huflib)