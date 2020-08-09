#include "utils.h"

std::ifstream NFileUtils::OpenInputFile(const char *InFile) noexcept(false) {
    std::ifstream fin(InFile, std::ifstream::binary);

    if (fin.fail()) {
        throw std::runtime_error("Cannot open input file.");
    }
    return fin;
}

std::ofstream NFileUtils::OpenOutputFile(const char *OutFile) noexcept(false) {
    std::ofstream fout(OutFile, std::ifstream::binary);

    if (fout.fail()) {
        throw std::runtime_error("Cannot open output file.");
    }
    return fout;
}

void NFileUtils::SetToBegin(std::ifstream &s) {
    s.clear();
    s.seekg(0, std::ios::beg);
}
