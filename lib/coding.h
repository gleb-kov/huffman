#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

#include <array>
#include <algorithm>
#include <vector>
#include <iostream>

#include "bitcode.h"
#include "../utils/types.h"

namespace NHuffmanConfig {
    constexpr size_t ALPHA = 1 << 8;
    constexpr size_t CHECKSUM_MASK = 7;
}

struct TFrequencyCounter {
    size_t Count[8][NHuffmanConfig::ALPHA] = {};
    size_t Length = 0;

    TFrequencyCounter() = default;

    void Update(const uchar *buf, size_t len);

private:
    void DummyUpdate(const uchar *buf, size_t len);
};

class THuffmanTree {
private:
    struct TNode {
        TNode *Sub[2];
        char Symbol;
        // bool IsTerm;

        TNode() {
            Sub[0] = Sub[1] = nullptr;
            Symbol = 0;
            // IsTerm = false;
        }

        ~TNode() {
            delete Sub[0];
            delete Sub[1];
        }
    };

private:
    using TFreqArray = std::array<size_t, NHuffmanConfig::ALPHA>;
    using TCodesArray = std::array<TBitcode, NHuffmanConfig::ALPHA>;

private:
    TCodesArray Codes;
    char *Meta;
    TNode *Root = nullptr;

private:
    void EncodeMeta(const TFreqArray &);

public:
    uchar RemainingBits = 0;

    //TODO : check type
    uchar CountRemainingBits(const TFreqArray &);

public:
    THuffmanTree() = default;

    explicit THuffmanTree(const TFrequencyCounter &);

    [[nodiscard]] const char *GetMeta() const;

    ~THuffmanTree();
};

#endif //HUFFMAN_CODING_H
