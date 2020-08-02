#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

#include <array>
#include <algorithm>
#include <vector>
#include <iostream>

#include "bitcode.h"
#include "../utils/types.h"

// TODO: check cast between char and uchar everywhere
// TODO: more const and static and attributes

namespace NHuffmanConfig {
    constexpr size_t ALPHA = 1 << 8;
    constexpr size_t CHECKSUM_MASK = 7;
    constexpr size_t META_BUF_SIZE = ALPHA * 4 + sizeof(uchar); // TODO: make 8
}

/***************************** TFrequencyCounter *****************************/

struct TFrequencyCounter {
    static constexpr size_t MAGIC = 8;

    size_t Count[MAGIC][NHuffmanConfig::ALPHA] = {};
    size_t Length = 0;

    TFrequencyCounter() = default;

    void Update(const uchar *buf, size_t len);

private:
    void DummyUpdate(const uchar *buf, size_t len);
};

/***************************** TFrequencyStorage *****************************/

class TFrequencyStorage {
    std::array<size_t, NHuffmanConfig::ALPHA> Storage = {};

public:
    TFrequencyStorage(const TFrequencyCounter&);

    // used to restore Huffman tree
    TFrequencyStorage(const uchar *meta);

    char *EncodeMeta(uchar remainingBits) const;

    size_t operator[](size_t ind) const;
};

/******************************* THuffmanTree ********************************/

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
    std::array<TBitcode, NHuffmanConfig::ALPHA> Codes;

    // in case of encoding
    char *Meta = nullptr;

    // in case of decoding
    TNode *Root = nullptr;

private:
    void EncodeMeta(const TFrequencyStorage &);

    uchar CountRemainingBits(const TFrequencyStorage &) const;

public:
    THuffmanTree() = default;

    explicit THuffmanTree(const TFrequencyStorage &);

    [[nodiscard]] const char *GetMeta() const;

    ~THuffmanTree();
};

#endif //HUFFMAN_CODING_H
