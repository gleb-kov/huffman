#include "coding.h"

/***************************** TFrequencyCounter *****************************/

void TFrequencyCounter::Update(const uchar *begin, size_t len) {
    Length += len;
    // parallel
}

void TFrequencyCounter::DummyUpdate(const uchar *buf, size_t len) {
    size_t it = (len >> 3) << 3;
    for (size_t i = 0; i < it;) {
        ++Count[0][buf[i++]];
        ++Count[1][buf[i++]];
        ++Count[2][buf[i++]];
        ++Count[3][buf[i++]];
        ++Count[4][buf[i++]];
        ++Count[5][buf[i++]];
        ++Count[6][buf[i++]];
        ++Count[7][buf[i++]];
    }
    while (it < len) {
        ++Count[0][buf[it++]];
    }
}

/******************************* THuffmanTree ********************************/

THuffmanTree::THuffmanTree(const TFrequencyCounter &fc) {

}

THuffmanTree::~THuffmanTree() {
    delete root;
}

