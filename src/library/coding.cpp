#include <algorithm>
#include <cstring>
#include <vector>

#include "coding.h"

using namespace NConfig::NHuffmanCoding;

/***************************** TFrequencyCounter *****************************/

void TFrequencyCounter::Update(const char *buf, size_t len) {
    Length += len;
    UpdateImpl(buf, len);
}

void TFrequencyCounter::UpdateImpl(const char *buf, size_t len) {
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
        for (size_t j = 0; j < ALPHA; j++) {
            Storage[j] += fc.Count[i][j];
        }
    }
}

TFrequencyStorage::TFrequencyStorage(const char *meta) {
    memcpy(Storage.data(), meta, sizeof(Storage));
}

char *TFrequencyStorage::EncodeMeta() const {
    char *meta = new char[META_BUFFER_SIZE];
    memcpy(meta, Storage.data(), sizeof(Storage));
    return meta;
}

size_t TFrequencyStorage::operator[](size_t ind) const {
    return Storage[ind];
}

/********************************** TBitCode *********************************/

size_t TBitCode::GetSize() const noexcept {
    return Size;
}

size_t TBitCode::operator[](size_t ind) const {
    return Code[ind - 1] ? 1 : 0;
}

void TBitCode::SetZero() noexcept {
    Size++;
}

void TBitCode::SetOne() noexcept {
    Code[Size++] = true;
}

void TBitCode::Reverse() {
    for (size_t i = 1; i <= Size - i; i++) {
        bool tmp = Code[i - 1];
        Code[i - 1] = Code[Size - i];
        Code[Size - i] = tmp;
    }
}

/******************************* THuffmanTree ********************************/

THuffmanTree::THuffmanTree(const TFrequencyStorage &fs) {
    std::array<std::pair<size_t, size_t>, ALPHA> salph = {};
    for (size_t i = 0; i < ALPHA; i++) {
        salph[i] = {fs[i], i};
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

    for (auto &code : Codes) {
        code.Reverse();
    }
    EncodeMeta(fs);
}

THuffmanTree::~THuffmanTree() {
    delete[] Meta;
}

void THuffmanTree::EncodeMeta(const TFrequencyStorage &fs) {
    Meta = fs.EncodeMeta();
}

void THuffmanTree::Restore() {
    if (Root) { // already has tree
        return;
    }
    Root = std::make_shared<TNode>();
    for (size_t i = 0; i < ALPHA; i++) {
        TNode *cur = Root.get();
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

TBitTree THuffmanTree::GetRoot() {
    return TBitTree(Root);
}

THuffmanTree::TCodesArray THuffmanTree::GetCodes() const {
    return Codes;
}

TBitCode THuffmanTree::GetBitCode(uchar symb) const {
    return Codes[symb];
}
