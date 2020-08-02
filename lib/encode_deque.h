#ifndef HUFFMAN_ENCODE_DEQUE_H
#define HUFFMAN_ENCODE_DEQUE_H

#include "bitcode.h"

struct encode_deque {
    void operator+=(const TBitcode&);
};


#endif //HUFFMAN_ENCODE_DEQUE_H
