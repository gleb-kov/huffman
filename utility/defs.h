#ifndef HUFFMAN_UTILITY_DEFS_H
#define HUFFMAN_UTILITY_DEFS_H

#include <fstream>

#include "../utils/defs.h"
#include "../lib/coding.h"

namespace NHuffmanUtil {

    constexpr size_t READ_BUFFER_SIZE = 1024;

    void Compress(const char *InFile, const char *OutFile);

    void Decompress(const char *InFile, const char *OutFile);

}

#endif //UFFMAN_UTILITY_DEFS_H
