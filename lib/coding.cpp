#include <cstring>

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

/******************************* THuffmanTree ********************************/

//TODO: check cnt in size_t

THuffmanTree::THuffmanTree(const TFrequencyCounter &fc) {
    using NHuffmanConfig::ALPHA;

    TFreqArray cnt = {};

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 256; j++) {
            cnt[j] += fc.Count[i][j];
        }
    }

    std::array<std::pair<size_t, size_t>, ALPHA> salph = {};
    for (size_t i = 0; i < ALPHA; i++) { // TODO: WTF
        salph[i] = {cnt[i], i};
        salph[i].second = i;
    }
    std::stable_sort(salph.begin(), salph.end());
    std::vector<std::pair<uint32_t, std::vector<size_t>>> huff;

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

    for (size_t i = 0; i < 256; i++) {
        Codes[i].Reverse();
    }

    EncodeMeta(cnt);
    CountRemainingBits(cnt);
}

void THuffmanTree::EncodeMeta(const TFreqArray &fa) {
    Meta = new char[1024];

    for (uint i = 0; i < 256; i++) {
        size_t cur = fa[i];
        Meta[4 * i + 3] = (unsigned char) (cur);
        Meta[4 * i + 2] = (unsigned char) (cur >>= 8);
        Meta[4 * i + 1] = (unsigned char) (cur >>= 8);
        Meta[4 * i] = (unsigned char) (cur >>= 8);
    }

    /*
     * TODO: replace with when decoding meta works
     *
    static constexpr size_t BUF_SIZE = NHuffmanConfig::ALPHA * sizeof(size_t);
    Meta = new char[BUF_SIZE];
    memcpy(Meta, fa.data(), BUF_SIZE);
     */
}

// count remaining bits, used check sum
uchar THuffmanTree::CountRemainingBits(const TFreqArray &fa) {
    size_t total = 0;
    for (size_t i = 0; i < NHuffmanConfig::ALPHA; i++) {
        total += fa[i] * Codes[i].GetSize();
        total &= NHuffmanConfig::CHECKSUM_MASK;
    }
    RemainingBits = (total % 8 ? 8 - (total % 8) : 0); // TODO: just total
    return total; // length of encoded part mod 8
}

const char *THuffmanTree::GetMeta() const {
    return Meta;
}

THuffmanTree::~THuffmanTree() {
    delete Root;
    delete[] Meta;
}
