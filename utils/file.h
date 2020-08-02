#ifndef HUFFMAN_FILE_H
#define HUFFMAN_FILE_H

#include <fstream>

namespace NFileUtils {

    std::ifstream OpenInputFile(const char *InFile) noexcept(false) {
        std::ifstream fin(InFile, std::ifstream::binary);

        if (fin.fail()) {
            throw std::runtime_error("Cannot open input file.\n");
        }
        return fin;
    }

    std::ofstream OpenOutputFile(const char *OutFile) noexcept (false) {
        std::ofstream fout(OutFile);

        if (fout.fail()) {
            throw std::runtime_error("Cannot open output file.\n");
        }
        return fout;
    }

}

#endif //HUFFMAN_FILE_H
