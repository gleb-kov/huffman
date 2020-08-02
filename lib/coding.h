#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

#include "../utils/types.h"

struct TFrequencyCounter {
    static constexpr size_t ALPHA = sizeof(uchar);

    size_t Count[8][ALPHA] = {};
    size_t Length;

    TFrequencyCounter() = default;

    void Update(const uchar *buf, size_t len);

private:
    void DummyUpdate(const uchar *buf, size_t len);
};

class THuffmanTree {
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

    TNode *root = nullptr;
public:
    THuffmanTree() = default;

    explicit THuffmanTree(const TFrequencyCounter&);

    ~THuffmanTree();
};

#endif //HUFFMAN_CODING_H
