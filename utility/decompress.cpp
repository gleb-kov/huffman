#include "defs.h"

void NHuffmanUtil::Decompress(const char *InFile, const char *OutFile) {
    std::ifstream fin = NFileUtils::OpenInputFile(InFile);
    std::ofstream fout = NFileUtils::OpenOutputFile(OutFile);

    uchar RBUF[META_BUFFER_SIZE];
    fin.read((char *) RBUF, sizeof(RBUF));

    if (fin.gcount() != sizeof(RBUF)) {
        throw std::runtime_error("Input file was damaged. Cannot restore Huffman tree.\n");
    }

    uchar remainingBits = RBUF[META_BUFFER_SIZE - 1]; // TODO: check correctness
    // TODO: check if it's EOF when bad... ?

    TFrequencyStorage fs(RBUF);
    //THuffmanTree hft(fs);

    // TODO: decompress
}

