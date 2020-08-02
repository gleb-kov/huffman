#ifndef HUFFMAN_BITCODE_H
#define HUFFMAN_BITCODE_H

#include <bitset>

#include "../utils/types.h"

class TBitcode {
    static constexpr size_t ALPHA = 1 << 8;

    std::bitset<ALPHA> Code;
    size_t Size = 0;

public:
    TBitcode() = default;

    [[nodiscard]] size_t GetSize() const noexcept;

    //bool operator[]

    void SetZero() noexcept;

    void SetOne() noexcept;

    [[deprecated]] void Reverse();
};

#endif //HUFFMAN_BITCODE_H
