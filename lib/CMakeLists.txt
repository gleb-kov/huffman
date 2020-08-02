cmake_minimum_required(VERSION 3.16)

add_library(huflib STATIC
        bitcode.h
        bitcode.cpp

        encode_deque.h
        encode_deque.cpp

        coding.h
        coding.cpp)