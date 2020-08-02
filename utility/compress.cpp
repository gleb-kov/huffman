#include "defs.h"

void NHuffmanUtil::Compress(const char *InFile, const char *OutFile) {
    std::ifstream fin = NFileUtils::OpenInputFile(InFile);
    std::ofstream fout = NFileUtils::OpenOutputFile(OutFile);

    uchar RBUF[READ_BUFFER_SIZE];
    TFrequencyCounter fc;

    while (fin) {
        fin.read((char *) RBUF, sizeof(RBUF));
        fc.Update(RBUF, fin.gcount());
    }
    // put fin to start of file
    fin.clear();
    fin.seekg(0, std::ios::beg);

    TFrequencyStorage fs(fc);
    THuffmanTree hft(fs);
    fout.write(hft.GetMeta(), NHuffmanConfig::META_BUF_SIZE);

    // TODO: compress

    while (fin) {
        fin.read((char *) RBUF, sizeof(RBUF));
        //for (size_t i = 0; i < (size_t) fin.gcount(); i++)
    }
}
