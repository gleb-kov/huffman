#ifndef HUFFMAN_CONFIG_H
#define HUFFMAN_CONFIG_H

#include "utils/utils.h"

/*
 * WARN: Parallel computations are not implemented yet.
 * Coding would be paralleled if USE_PARALLEL = true and processed buffer size >= BUFFER_MIN_SIZE
 */

namespace NConfig {

    namespace NParallelUtils {
        constexpr size_t THREADS_CNT = 8;

        constexpr size_t BUFFER_MIN_SIZE = 4096000;
    }

    namespace NHuffmanCoding {
        constexpr size_t ALPHA = 1 << 8;

        constexpr size_t META_BUFFER_SIZE = ALPHA * sizeof(size_t);

        constexpr bool USE_PARALLEL = false; // count frequency
    }

    namespace NHuffmanUtility {
        using NHuffmanCoding::META_BUFFER_SIZE;

        using BENCHMARK_CLOCK = NTimeUtils::BENCHMARK_CLOCK;

        constexpr size_t READ_BUFFER_SIZE = 1024;

        constexpr size_t DECODE_BUFFER_SIZE = 1024;

        constexpr bool USE_PARALLEL = false; // encode
    }

}

#endif //HUFFMAN_CONFIG_H
