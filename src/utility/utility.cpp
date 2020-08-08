#include "utility.h"

#include <iostream>

using namespace NHuffmanUtility;

void PrintStage(const std::string &stage, TBenchStageTimer &stageTimer) {
    std::cout << "Stage: " << stage << "; finished in: "
              << stageTimer.StopStage<std::chrono::milliseconds>().count() << " milliseconds." << std::endl;
}

void NHuffmanUtility::Compress(const char *InFile, const char *OutFile,
                               TBenchStageTimer &stageTimer, bool verbose) {
    std::ifstream fin = NFileUtils::OpenInputFile(InFile);
    std::ofstream fout = NFileUtils::OpenOutputFile(OutFile);

    stageTimer.StartStage();

    uchar RBUF[READ_BUFFER_SIZE];
    TFrequencyCounter fc;

    while (fin) {
        fin.read((char *) RBUF, sizeof(RBUF));
        fc.Update(RBUF, fin.gcount());
    }

    if (verbose) {
        PrintStage("calculate frequency", stageTimer);
    }

    // put fin to start of file
    fin.clear();
    fin.seekg(0, std::ios::beg);

    TFrequencyStorage fs(fc);
    THuffmanTree hft(fs);
    fout.write(hft.GetMeta(), META_BUFFER_SIZE);

    if (verbose) {
        PrintStage("build codes and write meta", stageTimer);
    }

    // TODO: compress

    /*while (fin) {
        fin.read((char *) RBUF, sizeof(RBUF));
        //for (size_t i = 0; i < (size_t) fin.gcount(); i++)
    }*/
}

void NHuffmanUtility::Decompress(const char *InFile, const char *OutFile,
                                 NTimeUtils::TStageTimer<BENCHMARK_CLOCK> &stageTimer, bool verbose) {
    std::ifstream fin = NFileUtils::OpenInputFile(InFile);
    std::ofstream fout = NFileUtils::OpenOutputFile(OutFile);

    stageTimer.StartStage();

    uchar RBUF[META_BUFFER_SIZE];
    fin.read((char *) RBUF, sizeof(RBUF));

    if (fin.gcount() != sizeof(RBUF)) {
        throw std::runtime_error("Input file was damaged. Cannot restore Huffman tree.");
    }

    // TODO: check if total size of fs != total decoded

    if (verbose) {
        PrintStage("read meta and restore Huffman tree", stageTimer);
    }

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
