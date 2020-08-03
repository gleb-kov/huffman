#ifndef HUFFMAN_BITCODE_H
#define HUFFMAN_BITCODE_H

#include <bitset>

#include "../utils/defs.h"

//TODO: optimize with deque of ints, it's easy to reverse and convert to string

class TBitcode {
    static constexpr size_t ALPHA = 1 << 8;

    std::bitset<ALPHA> Code;
    size_t Size = 0;

public:
    TBitcode() = default;

    [[nodiscard]] size_t GetSize() const noexcept;

    // TODO: rewrite
    size_t operator[](size_t ind) const;

    void SetZero() noexcept;

    void SetOne() noexcept;

    [[deprecated]] void Reverse();
};

#endif //HUFFMAN_BITCODE_H
