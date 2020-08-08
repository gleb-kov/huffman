#ifndef HUFFMAN_UTILITY_DEFS_H
#define HUFFMAN_UTILITY_DEFS_H

#include "../utils/utils.h"
#include "../library/coding.h"
#include "../library/coding_buffers.h"
#include "../config.h"

namespace NHuffmanUtility {

    using namespace NConfig::NHuffmanUtility;

    void Compress(const char *InFile, const char *OutFile);

    void Decompress(const char *InFile, const char *OutFile);

}

#endif //UFFMAN_UTILITY_DEFS_H
