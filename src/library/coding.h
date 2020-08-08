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
    static constexpr size_t ALPHA = std::numeric_limits<uchar>::max();

    size_t Count[MAGIC][ALPHA] = {};
    size_t Length = 0;

    TFrequencyCounter() = default;

    void Update(const char *buf, size_t len);

private:
    void UpdateImpl(const char *buf, size_t len);
};

/***************************** TFrequencyStorage *****************************/

class TFrequencyStorage {
    std::array<size_t, TFrequencyCounter::ALPHA> Storage = {};

public:
    static constexpr size_t META_BUFFER_SIZE =
            TFrequencyCounter::ALPHA * sizeof(size_t);

    explicit TFrequencyStorage(const TFrequencyCounter &);

    // used to restore Huffman tree
    explicit TFrequencyStorage(const char *meta);

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

    [[nodiscard]] size_t GetSize() const noexcept;

    size_t operator[](size_t ind) const;

    void SetZero() noexcept;

    void SetOne() noexcept;

    void Reverse();
};

/***************************** THuffmanTreeNode **************************/

struct THuffmanTreeNode {
    THuffmanTreeNode *Sub[2]; // nobody get direct access
    char Symbol;
    bool IsTerm;

    THuffmanTreeNode() {
        Sub[0] = Sub[1] = nullptr;
        Symbol = 0;
        IsTerm = false;
    }

    ~THuffmanTreeNode() {
        delete Sub[0];
        delete Sub[1];
    }
};

/********************************** TBitTree *********************************/

class TBitTree {
    std::shared_ptr<THuffmanTreeNode> Root;
    THuffmanTreeNode *State;

public:
    explicit TBitTree(std::shared_ptr<THuffmanTreeNode> &root) : Root(root) {}

    ~TBitTree() = default;

    /* Pre: bit equals 0 or 1 */
    void GoBy(size_t bit) {
        State = State->Sub[bit];
    }

    void GoByZero() {
        GoBy(0);
    }

    void GoByOne() {
        GoBy(1);
    }

    [[nodiscard]] bool IsValidState() const {
        // either parent of two subtrees or leaf
        if (State && State->Sub[0] && State->Sub[1] && !State->IsTerm) {
            return true;
        }
        if (State && !State->Sub[0] && !State->Sub[1] && State->IsTerm) {
            return true;
        }
        return false;
    }

    [[nodiscard]] bool IsTerm() const {
        return State->IsTerm;
    }

    /* Pre: IsTerm == true */
    [[nodiscard]] char GetSymbol() const {
        return State->Symbol;
    }
};

/******************************* THuffmanTree ********************************/

class THuffmanTree {
public:
    using TCodesArray = std::array<TBitCode, TFrequencyCounter::ALPHA>;
    using TNode = THuffmanTreeNode;

private:
    TCodesArray Codes;

    // in case of encoding
    char *Meta = nullptr; // no need for smart ptr

    // in case of decoding
    std::shared_ptr<TNode> Root;

private:
    void EncodeMeta(const TFrequencyStorage &);

public:
    explicit THuffmanTree(const TFrequencyStorage &);

    ~THuffmanTree();

    void Restore();

    [[nodiscard]] const char *GetMeta() const;

    [[nodiscard]] TBitTree GetRoot();

    [[nodiscard]] TCodesArray GetCodes() const;

    [[nodiscard]] TBitCode GetBitCode(uchar symb) const;
};

#endif //HUFFMAN_CODING_H
