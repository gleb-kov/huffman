#ifndef HUFFMAN_CODING_BUFFERS_H
#define HUFFMAN_CODING_BUFFERS_H

#include "coding.h"

/***************************** TSimpleCodingBuffer ***************************/
/*
 * ONE THREADED ENCODER AND DECODER
 */


template<size_t BUF_SIZE>
struct TSimpleCodingBuffer {
protected:
    char Result[BUF_SIZE] = {};
    size_t Size = 0;

    uchar *Tail = nullptr;
    size_t TailLen = 0;

public:
    TSimpleCodingBuffer() = default;

    virtual void Process(uchar *buf, size_t len) = 0;

    [[nodiscard]] bool Empty() const {
        return Size == 0 && TailLen == 0;
    }

    [[nodiscard]] char *Get() {
        return Result;
    }

    [[nodiscard]] size_t GetSize() const {
        return Size;
    }

    [[nodiscard]] bool IsFull() const {
        return Size == BUF_SIZE;
    }

    void ClearBuffer() {
        Size = 0;
        Process(Tail, TailLen);
    }
};

/***************************** TEncodeBuffer *********************************/

template<size_t BUF_SIZE>
class TEncodeBuffer : public TSimpleCodingBuffer<BUF_SIZE> {
    THuffmanTree::TCodesArray Codes;

public:
    TEncodeBuffer(THuffmanTree &tree)
            : TSimpleCodingBuffer<BUF_SIZE>(), Codes(tree.GetCodes()) {}

    void Process(uchar *buf, size_t len) override {
        // TODO
    }
};

/***************************** TDecodeBuffer *********************************/

template<size_t BUF_SIZE>
class TDecodeBuffer : public TSimpleCodingBuffer<BUF_SIZE> {
    THuffmanTreeNode *Root; // TODO: shared_ptr

public:
    explicit TDecodeBuffer(THuffmanTree &tree)
            : TSimpleCodingBuffer<BUF_SIZE>() {
        tree.Restore();
        Root = tree.GetRoot();
    };

    void Process(uchar *buf, size_t len) override {
        // assert(Tail == nullptr); ?? what if call from clear()?
        // TODO
    }
};

#endif //HUFFMAN_CODING_BUFFERS_H
