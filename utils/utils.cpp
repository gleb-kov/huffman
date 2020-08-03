#include "utils.h"

std::ifstream NFileUtils::OpenInputFile(const char *InFile) noexcept(false) {
    std::ifstream fin(InFile, std::ifstream::binary); // TODO: std::ios::binary | std::ios::ate ???

    if (fin.fail()) {
        throw std::runtime_error("Cannot open input file.\n");
    }
    return fin;
}

std::ofstream NFileUtils::OpenOutputFile(const char *OutFile) noexcept(false) {
    std::ofstream fout(OutFile);

    if (fout.fail()) {
        throw std::runtime_error("Cannot open output file.\n");
    }
    return fout;
}
