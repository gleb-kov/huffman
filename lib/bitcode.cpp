#include "bitcode.h"

// TODO: check if possible, move to header or even to coding.h

size_t TBitcode::GetSize() const noexcept {
    return Size;
}

void TBitcode::SetZero() noexcept {
    Size++;
}

void TBitcode::SetOne() noexcept {
    Code[Size++] = true;
}

void TBitcode::Reverse() {
    for (size_t i = 1; i <= Size - i; i++) {
        bool tmp = Code[i - 1];
        Code[i - 1] = Code[Size - i];
        Code[Size - i] = tmp;
    }
}