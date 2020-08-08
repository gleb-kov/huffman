#include <iostream>
#include <cstring>

#include "utility.h"

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        std::cout << "Сonsole utility for compressing/decompressing files using Huffman coding" << std::endl;
        std::cout << "Usage: [opts] <mode> <input file> <output file>" << std::endl;
        std::cout << "[opts]:" << std::endl;
        std::cout << "-v, --verbose                 Verbose." << std::endl;
        std::cout << "<mode>:" << std::endl;
        std::cout << "-c, --compress, --encode      Compress file." << std::endl;
        std::cout << "-d, --decompress, --decode    Decompress file." << std::endl;
        return 0;
    } else if (argc != 4 && argc != 5) {
        std::cerr << "Incorrect arguments. --help for more information." << std::endl;
        return 1;
    }

    bool verbose = false;

    if (strcmp(argv[1], "-v") == 0 ||  strcmp(argv[1], "--verbose") == 0) {
        verbose = true;
        argc--;
        argv++;
    }

    char mode = 0;

    if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0 || strcmp(argv[1], "--encode") == 0) {
        mode = 1;
    }
    if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0 || strcmp(argv[1], "--decode") == 0) {
        mode = 2;
    }
    if (mode == 0) {
        std::cerr << "Incorrect mode or options. --help for more information." << std::endl;
        return 1;
    }

    NHuffmanUtility::TBenchStageTimer stageTimer;
    auto startTime = stageTimer.GetStageStart();

    try {
        if (mode == 1) {
            NHuffmanUtility::Compress(argv[2], argv[3], stageTimer, verbose);
        } else {
            NHuffmanUtility::Decompress(argv[2], argv[3], stageTimer, verbose);
        }
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    if (verbose) {
        auto elapsedMs = stageTimer.DurationSince<std::chrono::milliseconds>(startTime);
        std::cout << "Finished in " << std::fixed << elapsedMs.count() << " milliseconds." << std::endl;
    }

    return 0;
}
