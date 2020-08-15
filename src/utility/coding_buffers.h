#ifndef HUFFMAN_CODING_BUFFERS_H
#define HUFFMAN_CODING_BUFFERS_H

#include "src/library/coding.h"

/***************************** TSimpleCodingBuffer ***************************/

/*
 * ONE THREADED ENCODER AND DECODER
 */

template<size_t BUF_SIZE, size_t EXTRA = 0>
struct TSimpleCodingBuffer {
protected:
    char Result[BUF_SIZE + EXTRA] = {};

    const size_t Total = 0;
    size_t Processed = 0;
    size_t Size = 0;

    size_t TailLen = 0;
    char *Tail = nullptr;

protected:
    void SetTail(char *buf, size_t len) {
        if (len) {
            Tail = buf;
            TailLen = len;
        }
    }

    void Write(char symbol) {
        Processed++;
        if (Processed <= Total) {
            Result[Size++] = symbol;
        }
    }

    bool IsStopped() const {
        return Processed >= Total;
    }

    void ProcessTail() {
        char *tptr = std::exchange(Tail, nullptr);
        size_t tlen = std::exchange(TailLen, 0);
        Process(tptr, tlen);
    }

public:
    explicit TSimpleCodingBuffer(size_t total) : Total(total) {}

    virtual void Process(char *buf, size_t len) = 0;

    bool Empty() const {
        return Size == 0 && TailLen == 0;
    }

    char *Get() {
        return Result;
    }

    size_t GetSize() const {
        return Size;
    }

    bool IsFull() const {
        return Size >= BUF_SIZE;
    }

    void ClearBuffer() {
        Size = 0;
        ProcessTail();
    }
};

/***************************** TEncodeBuffer *********************************/

template<size_t BUF_SIZE, size_t EXTRA = TFrequencyCounter::ALPHA / CHBITS>
class TEncodeBuffer : public TSimpleCodingBuffer<BUF_SIZE, EXTRA> {
    static_assert(EXTRA >= TFrequencyCounter::ALPHA / CHBITS);

    THuffmanTree::TCodesArray Codes;
    size_t RemLen = 8;
    uchar Remainder = 0;

public:
    explicit TEncodeBuffer(THuffmanTree &tree)
            : TSimpleCodingBuffer<BUF_SIZE, EXTRA>(tree.GetTotal()), Codes(tree.GetCodes()) {}

    void Process(char *buf, size_t len) override {
        while (len && !this->IsFull() && !this->IsStopped()) {
            uchar cur = *reinterpret_cast<uchar*>(&buf[0]);
            for (size_t i = 0; i < Codes[cur].GetSize(); i++) {
                Remainder <<= 1;
                Remainder |= Codes[cur][i];
                RemLen--;
                if (RemLen == 0) {
                    this->Write(Remainder);
                    RemLen = 8;
                }
            }
            len--, buf++;
        }
        this->SetTail(buf, len);
    }

    void SetRemaining() {
        this->Size = 0;
        if (RemLen != 8) {
            Remainder <<= RemLen;
            this->Write(Remainder);
        }
    }
};

/***************************** TDecodeBuffer *********************************/

template<size_t BUF_SIZE>
class TDecodeBuffer : public TSimpleCodingBuffer<BUF_SIZE, CHBITS> {
    TBitTree Tree;

    static constexpr uchar MASKS[8] = {1, 2, 4, 8, 16, 32, 64, 128};

    bool Valid = true;

public:
    explicit TDecodeBuffer(THuffmanTree &tree)
            : TSimpleCodingBuffer<BUF_SIZE, CHBITS>(tree.GetTotal()), Tree(tree.GetRoot()) {}

    void Process(char *buf, size_t len) override {
        while (len && !this->IsFull() && !this->IsStopped()) {
            uchar cur = *reinterpret_cast<uchar *>(&buf[0]);

            for (size_t i = 8; i > 0; i--) {
                uchar maskBit = (cur & MASKS[i - 1]) >> (i - 1);
                Tree.GoBy(maskBit);

                char symbol = Tree.GetSymbol();
                if (Tree.IsTerm()) {
                    this->Write(symbol);
                }
            }
            len--, buf++;
        }
        if (this->IsStopped() && len > 0) {
            Valid = false;
        }
        this->SetTail(buf, len);
    }

    bool IsValid() const {
        return Valid;
    }
};

#endif //HUFFMAN_CODING_BUFFERS_H
