#ifndef HUFFMAN_UTILITY_DEFS_H
#define HUFFMAN_UTILITY_DEFS_H

#include <fstream>

#include "../utils/defs.h"
#include "../lib/coding.h"

// TODO: replace with one-include file

namespace NHuffmanUtil {

    constexpr size_t READ_BUFFER_SIZE = 1024; // TODO: fix when meta would be 2048

    constexpr size_t META_BUFFER_SIZE = NHuffmanConfig::META_BUF_SIZE;

    void Compress(const char *InFile, const char *OutFile);

    void Decompress(const char *InFile, const char *OutFile);

}

#endif //UFFMAN_UTILITY_DEFS_H
