#ifndef HUFFMAN_FILE_H
#define HUFFMAN_FILE_H

#include <fstream>

namespace NFileUtils {

    std::ifstream OpenInputFile(const char *InFile) noexcept(false);

    std::ofstream OpenOutputFile(const char *OutFile) noexcept(false);

}

#endif //HUFFMAN_FILE_H
