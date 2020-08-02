#include "coding.h"

/***************************** TFrequencyCounter *****************************/

void TFrequencyCounter::Update(const uchar *buf, size_t len) {
    Length += len;
    DummyUpdate(buf, len);
    // TODO: parallel
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

/***************************** TFrequencyStorage *****************************/

TFrequencyStorage::TFrequencyStorage(const TFrequencyCounter &fc) {
    for (size_t i = 0; i < TFrequencyCounter::MAGIC; i++) {
        for (size_t j = 0; j < NHuffmanConfig::ALPHA; j++) {
            Storage[j] += fc.Count[i][j];
        }
    }
}

TFrequencyStorage::TFrequencyStorage(const uchar *meta) {
    // TODO: replace 4 with 8 since size_t
    for (size_t i = 0; i < NHuffmanConfig::META_BUF_SIZE; i += 4) {
        Storage[i >> 2] = meta[i + 3] | (meta[i + 2] << 8)
                          | (meta[i + 1] << 16) | (meta[i] << 24);
    }
}

char * TFrequencyStorage::EncodeMeta(uchar remainingBits) const {
    using namespace NHuffmanConfig;
    char *meta = new char[META_BUF_SIZE];

    // TODO: unsafe cast

    for (uint i = 0; i < NHuffmanConfig::ALPHA; i++) {
        size_t cur = Storage[i];
        meta[4 * i + 3] = (unsigned char) (cur);
        meta[4 * i + 2] = (unsigned char) (cur >>= 8);
        meta[4 * i + 1] = (unsigned char) (cur >>= 8);
        meta[4 * i] = (unsigned char) (cur >>= 8);
    }
    meta[META_BUF_SIZE - 1] = remainingBits;
    return meta;
    /*
     * TODO: replace with memcpy when decoding meta works
     */
}

size_t TFrequencyStorage::operator[](size_t ind) const {
    return Storage[ind];
}

/******************************* THuffmanTree ********************************/

//TODO: check is cnt in size_t?

THuffmanTree::THuffmanTree(const TFrequencyStorage &fs) {
    using NHuffmanConfig::ALPHA;

    // TODO: refactor

    std::array<std::pair<size_t, size_t>, ALPHA> salph = {};
    for (size_t i = 0; i < ALPHA; i++) { // TODO: WTF
        salph[i] = {fs[i], i};
        salph[i].second = i;
    }
    std::stable_sort(salph.begin(), salph.end());
    std::vector<std::pair<uint32_t, std::vector<size_t>>> huff; // TODO

    size_t c1 = 0, c2 = 0;

    while (c1 < ALPHA || c2 < huff.size()) {
        uint32_t w1 = UINT32_MAX, w2 = UINT32_MAX, w3 = UINT32_MAX;

        if (c1 + 1 < salph.size()) {
            w1 = salph[c1].first + salph[c1 + 1].first;
        }
        if (c1 < salph.size() && c2 < huff.size()) {
            w2 = salph[c1].first + huff[c2].first;
        }
        if (c2 + 1 < huff.size()) {
            w3 = huff[c2].first + huff[c2 + 1].first;
        }

        if (w1 <= w2 && w1 <= w3 && c1 + 1 < salph.size()) {
            huff.push_back({w1, {salph[c1].second, salph[c1 + 1].second}});
            Codes[salph[c1].second].SetZero();
            Codes[salph[c1 + 1].second].SetOne();
            c1 += 2;
        } else if (w2 <= w1 && w2 <= w3 && c1 < salph.size() && c2 < huff.size()) {
            huff.push_back({w2, huff[c2].second});
            huff.back().second.push_back(salph[c1].second);
            Codes[salph[c1].second].SetOne();
            for (size_t i = 0; i < huff[c2].second.size(); i++) {
                Codes[huff[c2].second[i]].SetZero();
            }
            c1++;
            c2++;
        } else if (c2 + 1 < huff.size()) {
            huff.push_back({w3, {}});
            for (size_t i = 0; i < huff[c2].second.size(); i++) {
                Codes[huff[c2].second[i]].SetZero();
                huff.back().second.push_back(huff[c2].second[i]);
            }
            for (size_t i = 0; i < huff[c2 + 1].second.size(); i++) {
                Codes[huff[c2 + 1].second[i]].SetOne();
                huff.back().second.push_back(huff[c2 + 1].second[i]);
            }
            c2 += 2;
        } else {
            break;
        }
    }

    for (size_t i = 0; i < ALPHA; i++) {
        Codes[i].Reverse();
    }

    EncodeMeta(fs);
}

void THuffmanTree::EncodeMeta(const TFrequencyStorage &fs) {
    uchar remainingBits = CountRemainingBits(fs);
    Meta = fs.EncodeMeta(remainingBits);
}

// count remaining bits, used check sum
uchar THuffmanTree::CountRemainingBits(const TFrequencyStorage &fs) const {
    size_t total = 0;
    for (size_t i = 0; i < NHuffmanConfig::ALPHA; i++) {
        total += fs[i] * Codes[i].GetSize();
        total &= NHuffmanConfig::CHECKSUM_MASK;
    }
    // TODO: just total, use mask from config
    return (total % 8 ? 8 - (total % 8) : 0); // length of encoded part mod 8
}

void THuffmanTree::BuildTree() {
    // TODO: refactor

    Root = new TNode();
    for (size_t i = 0; i < NHuffmanConfig::ALPHA; i++) {
        TNode *cur = Root;
        for (size_t j = 0; j < Codes[i].GetSize(); j++) {
            size_t sub = Codes[i][j];
            if (!cur->Sub[sub]) {
                cur->Sub[sub] = new TNode;
            }
            cur = cur->Sub[sub];
        }
        cur->IsTerm = true;
        cur->Symbol = (char) i;
    }
}

const char *THuffmanTree::GetMeta() const {
    return Meta;
}

THuffmanTree::~THuffmanTree() {
    delete Root;
    delete[] Meta;
}
