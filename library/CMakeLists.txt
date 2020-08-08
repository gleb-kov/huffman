cmake_minimum_required(VERSION 3.16)

add_library(huflib STATIC

        coding.h
        coding.cpp

        coding_buffers.h

        ../config.h)