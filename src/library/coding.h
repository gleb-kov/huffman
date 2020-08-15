#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

#include <array>
#include <bitset>
#include <memory>

#include "src/config.h"
#include "src/utils/utils.h"

/***************************** TFrequencyCounter *****************************/

struct TFrequencyCounter {
    static constexpr size_t MAGIC = 8;
    static constexpr size_t ALPHA = std::numeric_limits<uchar>::max() + 1;

    size_t Count[MAGIC][ALPHA] = {};
    size_t Length = 0;

    TFrequencyCounter() = default;

    void Update(const char *buf, size_t len);

private:
    void UpdateImpl(const uchar *buf, size_t len);
};

/***************************** TFrequencyStorage *****************************/

class TFrequencyStorage {
    std::array<size_t, TFrequencyCounter::ALPHA> Storage = {};
    size_t Total = 0;

private:
    void CalcTotal();

public:
    static constexpr size_t META_BUFFER_SIZE =
            TFrequencyCounter::ALPHA * sizeof(size_t);

    explicit TFrequencyStorage(const TFrequencyCounter &);

    // used to restore Huffman tree
    explicit TFrequencyStorage(const char *meta);

    size_t GetTotal() const;

    // pass buffer ownership
    [[nodiscard]] char *EncodeMeta() const;

    size_t operator[](size_t ind) const;
};

/********************************** TBitCode *********************************/

class TBitCode {
    std::bitset<TFrequencyCounter::ALPHA> Code;
    size_t Size = 0;

public:
    TBitCode() = default;

    size_t GetSize() const noexcept;

    size_t operator[](size_t ind) const;

    void SetZero() noexcept;

    void SetOne() noexcept;

    void Reverse();
};

/***************************** THuffmanTreeNode **************************/

struct THuffmanTreeNode {
    THuffmanTreeNode *Sub[2]{}; // nobody get direct access
    char Symbol;
    bool IsTerm;

    THuffmanTreeNode();

    ~THuffmanTreeNode();
};

/********************************** TBitTree *********************************/

class TBitTree {
    std::shared_ptr<THuffmanTreeNode> Root;
    THuffmanTreeNode *State = nullptr;

public:
    explicit TBitTree(std::shared_ptr<THuffmanTreeNode>);

    ~TBitTree() = default;

    /* Pre: bit equals 0 or 1 */
    void GoBy(size_t bit);

    bool IsTerm() const;

    /* Pre: IsTerm == true */
    char GetSymbol() const;
};

/******************************* THuffmanTree ********************************/

class THuffmanTree {
public:
    using TCodesArray = std::array<TBitCode, TFrequencyCounter::ALPHA>;
    using TNode = THuffmanTreeNode;

private:
    TCodesArray Codes;

    // in case of decoding
    std::shared_ptr<TNode> Root;

    size_t Total = 0;

    // in case of encoding
    char *Meta = nullptr; // no need for smart ptr

private:
    void EncodeMeta(const TFrequencyStorage &);

public:
    explicit THuffmanTree(const TFrequencyStorage &);

    ~THuffmanTree();

    void Restore();

    const char *GetMeta() const;

    [[nodiscard]] TBitTree GetRoot();

    [[nodiscard]] TCodesArray GetCodes() const;

    size_t GetTotal() const;
};

#endif //HUFFMAN_CODING_H
