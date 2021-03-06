#include <algorithm>
#include <cstring>
#include <deque>

#include "coding.h"

constexpr size_t ALPHA = TFrequencyCounter::ALPHA;

/***************************** TFrequencyCounter *****************************/

void TFrequencyCounter::Update(const char *buf, size_t len) {
    Length += len;
    UpdateImpl((uchar *)buf, len);
}

void TFrequencyCounter::UpdateImpl(const uchar *buf, size_t len) {
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
    CalcTotal();
}

TFrequencyStorage::TFrequencyStorage(const char *meta) {
    memcpy(Storage.data(), meta, sizeof(Storage));
    CalcTotal();
}

void TFrequencyStorage::CalcTotal() {
    for (size_t i = 0; i < Storage.size(); i++) {
        Total += Storage[i];
    }
}

size_t TFrequencyStorage::GetTotal() const noexcept {
    return Total;
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

uchar TBitCode::operator[](size_t ind) const {
    return Code[ind] ? 1 : 0;
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

/***************************** THuffmanTreeNode **************************/

THuffmanTreeNode::THuffmanTreeNode() {
    Sub[0] = Sub[1] = nullptr;
    Symbol = 0;
    IsTerm = false;
}

THuffmanTreeNode::~THuffmanTreeNode() {
    if (!IsTerm) {
        delete Sub[0];
        delete Sub[1];
    }
}

/********************************** TBitTree *********************************/

TBitTree::TBitTree(std::shared_ptr<THuffmanTreeNode> root)
        : Root(std::move(root)), State(Root.get()) {}

char TBitTree::GoBy(uchar bit) {
    State = State->Sub[bit];
    return State->Symbol;
}

bool TBitTree::IsTerm() const {
    return State->IsTerm;
}

char TBitTree::GetSymbol() const {
    return State->Symbol;
}

/******************************* THuffmanTree ********************************/

THuffmanTree::THuffmanTree(const TFrequencyStorage &fs)
        : Total(fs.GetTotal()) {
    std::array<std::pair<size_t, size_t>, ALPHA> salph = {};
    for (size_t i = 0; i < ALPHA; i++) {
        salph[i] = {fs[i], i};
    }

    std::stable_sort(salph.begin(), salph.end());
    std::deque<std::pair<ui64, std::deque<size_t>>> huff;

    size_t c1 = 0, c2 = 0;

    while (c1 < ALPHA || c2 < huff.size()) {
        ui64 w1 = Max<ui64>, w2 = Max<ui64>, w3 = Max<ui64>;

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
            huff.emplace_back(w2, huff[c2].second);
            huff.back().second.push_back(salph[c1].second);
            Codes[salph[c1].second].SetOne();
            for (size_t i : huff[c2].second) {
                Codes[i].SetZero();
            }
            c1++, c2++;
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
            uchar sub = Codes[i][j];
            if (!cur->Sub[sub]) {
                cur->Sub[sub] = new TNode;
            }
            cur = cur->Sub[sub];
        }
        cur->IsTerm = true;
        cur->Symbol = (char) i;
    }

    // graph closure
    std::deque<THuffmanTreeNode *> dq = {Root.get()};
    while (!dq.empty()) {
        THuffmanTreeNode *cur = dq.front();
        dq.pop_front();

        if (cur->IsTerm) {
            cur->Sub[0] = Root->Sub[0];
            cur->Sub[1] = Root->Sub[1];
        } else {
            dq.push_back(cur->Sub[0]);
            dq.push_back(cur->Sub[1]);
        }
    }
}

const char *THuffmanTree::GetMeta() const {
    return Meta;
}

TBitTree THuffmanTree::GetRoot() {
    Restore();
    return TBitTree(Root);
}

THuffmanTree::TCodesArray THuffmanTree::GetCodes() const {
    return Codes;
}

size_t THuffmanTree::GetTotal() const {
    return Total;
}
