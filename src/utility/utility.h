#ifndef HUFFMAN_UTILITY_DEFS_H
#define HUFFMAN_UTILITY_DEFS_H

#include "src/config.h"
#include "src/library/coding.h"
#include "src/library/coding_buffers.h"
#include "src/utils/utils.h"

namespace NHuffmanUtility {

    using namespace NConfig::NHuffmanUtility;

    void Compress(const char *InFile, const char *OutFile);

    void Decompress(const char *InFile, const char *OutFile);

}

#endif //UFFMAN_UTILITY_DEFS_H
