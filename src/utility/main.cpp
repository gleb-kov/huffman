#include <cstring>
#include <experimental/filesystem>
#include <iostream>

#include "utility.h"

// it's not in utils due to linkage with fs
uintmax_t FileSizeBytes(const char *file) noexcept(false) {
    namespace fs = std::experimental::filesystem;
    fs::path fsp = file;
    return fs::file_size(fsp);
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        std::cout << "Сonsole utility for compressing/decompressing files using Huffman coding" << std::endl;
        std::cout << "Github: https://github.com/gleb-kov/huffman" << std::endl << std::endl;

        std::cout << "Usage: [opts] <mode> <input file> <output file>" << std::endl << std::endl;

        std::cout << "[opts]:" << std::endl;
        std::cout << "-v, --verbose                 Verbose." << std::endl << std::endl;

        std::cout << "<mode>:" << std::endl;
        std::cout << "-c, --compress, --encode      Compress file." << std::endl;
        std::cout << "-d, --decompress, --decode    Decompress file." << std::endl;
        return 0;
    } else if (argc != 4 && argc != 5) {
        std::cerr << "Incorrect arguments. --help for more information." << std::endl;
        return 1;
    }

    bool verbose = false;

    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0) {
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
        std::cerr << "Incorrect arguments. --help for more information." << std::endl;
        return 1;
    }

    NHuffmanUtility::TBenchStageTimer stageTimer;

    try {
        if (mode == 1) {
            NHuffmanUtility::Compress(argv[2], argv[3], stageTimer, verbose);
        } else {
            NHuffmanUtility::Decompress(argv[2], argv[3], stageTimer, verbose);
        }
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    }

    if (verbose) {
        auto elapsedMs = stageTimer.SinceInit<std::chrono::milliseconds>();
        std::cout << "Finished in " << std::fixed << elapsedMs.count() << " milliseconds." << std::endl;
    }

    if (verbose && mode == 1) {
        std::cout << std::endl << "Compare file size:" << std::endl;
        uintmax_t before = FileSizeBytes(argv[2]);
        uintmax_t after = FileSizeBytes(argv[3]);
        std::cout << "Origin (" << argv[2] << "): " << before << " bytes" << std::endl;
        std::cout << "Encoded (" << argv[3] << "): " << after << " bytes" << std::endl;
        if (before >= after) {
            std::cout << "Saved space: " << (before - after) * 100.0 / before << "%";
        } else {
            std::cout << "Space overhead detected. It happens when origin file is too small.";
        }
        std::cout << std::endl;
    }

    return 0;
}
