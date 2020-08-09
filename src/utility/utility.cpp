#include <iostream>

#include "utility.h"

using namespace NHuffmanUtility;

void PrintStage(const std::string &stage, TBenchStageTimer &stageTimer, bool verbose) {
    if (verbose) {
        std::cout << "Stage: " << stage << "; finished in: "
                  << stageTimer.StopStage<std::chrono::milliseconds>().count() << " milliseconds." << std::endl;\

    }
}

template<size_t CODE_BUFFER_SIZE, size_t EXTRA>
void ProcessFilledBuffer(std::ofstream &fout, TSimpleCodingBuffer<CODE_BUFFER_SIZE, EXTRA> &coder) {
    while (coder.IsFull()) {
        fout.write(coder.Get(), coder.GetSize());
        coder.ClearBuffer();
    }
}

template<size_t READ_BUFFER_SIZE, size_t CODE_BUFFER_SIZE, size_t EXTRA>
inline void ProcessFile(std::ifstream &fin, std::ofstream &fout,
                        TSimpleCodingBuffer<CODE_BUFFER_SIZE, EXTRA> &coder, char *readBuffer) {
    while (fin) {
        fin.read(readBuffer, READ_BUFFER_SIZE);
        coder.Process(readBuffer, fin.gcount());
        ProcessFilledBuffer(fout, coder);
    }
}

void NHuffmanUtility::Compress(const char *InFile, const char *OutFile,
                               TBenchStageTimer &stageTimer, bool verbose) {
    std::ifstream fin = NFileUtils::OpenInputFile(InFile);
    std::ofstream fout = NFileUtils::OpenOutputFile(OutFile);

    char readBuffer[READ_BUFFER_SIZE];
    TFrequencyCounter fc;
    stageTimer.StartStage();

    while (fin) {
        fin.read(readBuffer, sizeof(readBuffer));
        fc.Update(readBuffer, fin.gcount());
    }

    PrintStage("calculate frequency", stageTimer, verbose);

    NFileUtils::SetToBegin(fin);

    TFrequencyStorage fs(fc);
    THuffmanTree hft(fs);
    fout.write(hft.GetMeta(), TFrequencyStorage::META_BUFFER_SIZE);

    PrintStage("build codes and write meta", stageTimer, verbose);

    auto encoder = TEncodeBuffer<DECODE_BUFFER_SIZE>(hft);
    ProcessFile<sizeof(readBuffer)>(fin, fout, encoder, readBuffer);

    if (!encoder.Empty()) {
        fout.write(encoder.Get(), encoder.GetSize());
    }
    encoder.SetRemaining();
    fout.write(encoder.Get(), encoder.GetSize());
}

void NHuffmanUtility::Decompress(const char *InFile, const char *OutFile,
                                 NTimeUtils::TStageTimer<BENCHMARK_CLOCK> &stageTimer, bool verbose) {
    std::ifstream fin = NFileUtils::OpenInputFile(InFile);
    std::ofstream fout = NFileUtils::OpenOutputFile(OutFile);

    stageTimer.StartStage();
    static_assert(TFrequencyStorage::META_BUFFER_SIZE <= READ_BUFFER_SIZE);

    char readBuffer[READ_BUFFER_SIZE];
    fin.read(readBuffer, sizeof(readBuffer));
    if (fin.gcount() < TFrequencyStorage::META_BUFFER_SIZE) {
        throw std::runtime_error("Input file was damaged. Cannot restore Huffman tree.");
    }

    PrintStage("read meta and restore Huffman tree", stageTimer, verbose);

    TFrequencyStorage fs(readBuffer);
    THuffmanTree hft(fs);
    auto decoder = TDecodeBuffer<DECODE_BUFFER_SIZE>(hft);

    decoder.Process(readBuffer + TFrequencyStorage::META_BUFFER_SIZE, fin.gcount() - TFrequencyStorage::META_BUFFER_SIZE);
    ProcessFilledBuffer(fout, decoder);
    ProcessFile<sizeof(readBuffer)>(fin, fout, decoder, readBuffer);

    while (!decoder.Empty()) {
        fout.write(decoder.Get(), decoder.GetSize());
        decoder.ClearBuffer();
    }
}
