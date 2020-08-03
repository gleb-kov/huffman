#ifndef HUFFMAN_CONFIG_H
#define HUFFMAN_CONFIG_H

#include "utils/defs.h"

namespace NConfig {

    //namespace NUtils {
        // constants for parallel calculations
    //}

    namespace NHuffmanCoding {
        constexpr size_t ALPHA = 1 << 8;
        constexpr size_t CHECKSUM_MASK = 7;
        constexpr size_t META_BUF_SIZE = ALPHA * 4 + sizeof(uchar); // TODO: make 8
    }

    namespace NHuffmanUtility {
        constexpr size_t READ_BUFFER_SIZE = 1024;

        constexpr size_t META_BUFFER_SIZE = NHuffmanCoding::META_BUF_SIZE;

        constexpr size_t DECODE_BUFFER_SIZE = 1024;
    }

}

#endif //HUFFMAN_CONFIG_H
