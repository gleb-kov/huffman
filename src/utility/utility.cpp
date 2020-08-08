#include "utility.h"

void NHuffmanUtility::Compress(const char *InFile, const char *OutFile) {
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
    fout.write(hft.GetMeta(), META_BUFFER_SIZE);

    // TODO: compress

    while (fin) {
        fin.read((char *) RBUF, sizeof(RBUF));
        //for (size_t i = 0; i < (size_t) fin.gcount(); i++)
    }
}

void NHuffmanUtility::Decompress(const char *InFile, const char *OutFile) {
    std::ifstream fin = NFileUtils::OpenInputFile(InFile);
    std::ofstream fout = NFileUtils::OpenOutputFile(OutFile);

    uchar RBUF[META_BUFFER_SIZE];
    fin.read((char *) RBUF, sizeof(RBUF));

    if (fin.gcount() != sizeof(RBUF)) {
        throw std::runtime_error("Input file was damaged. Cannot restore Huffman tree.\n");
    }

    // TODO: check if it's EOF when bad... ?

    TFrequencyStorage fs(RBUF);
    /*THuffmanTree hft(fs);
    auto decoder = TDecodeBuffer<DECODE_BUFFER_SIZE>(hft);

    // TODO: untested
    while (fin) {
        fin.read((char *) RBUF, sizeof(RBUF));
        decoder.Process(RBUF, fin.gcount());

        if (decoder.IsFull()) {
            fout.write(decoder.Get(), decoder.GetSize());
            decoder.ClearBuffer();
        }
    }

    while(!decoder.Empty()) {
        fout.write(decoder.Get(), decoder.GetSize());
        decoder.ClearBuffer();
    }*/
}
