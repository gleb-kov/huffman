cmake_minimum_required(VERSION 3.16)

add_library(huflib STATIC
        bitcode.h
        bitcode.cpp

        coding.h
        coding.cpp

        coding_buffers.h)