#ifndef HUFFMAN_UTILITY_DEFS_H
#define HUFFMAN_UTILITY_DEFS_H

#include "coding_buffers.h"
#include "src/config.h"
#include "src/library/coding.h"
#include "src/utils/utils.h"

namespace NHuffmanUtility {

    using namespace NConfig::NHuffmanUtility;

    using TBenchStageTimer = NTimeUtils::TStageTimer<BENCHMARK_CLOCK>;

    void Compress(const char *inFile, const char *outFile,
                  TBenchStageTimer &stageTimer, bool verbose);

    void Decompress(const char *inFile, const char *outFile,
                    TBenchStageTimer &stageTimer, bool verbose);

}

#endif //HUFFMAN_UTILITY_DEFS_H
