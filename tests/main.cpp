#include <algorithm>

#include "gtest/gtest.h"
#include "src/library/coding.h"

using NConfig::NHuffmanCoding::ALPHA;
using TFreqArray = std::array<size_t, ALPHA>;

std::string TextByFreq(const TFreqArray &arr) {
    std::string result;
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr[i]; j++) {
            result += (char) (i);
        }
    }
    return result;
}

bool MyTest(const TFreqArray &arr) {
    std::string buf = TextByFreq(arr);

    std::random_shuffle(buf.begin(), buf.end());

    TFrequencyCounter fc;
    fc.Update(buf.data(), buf.size());

    TFrequencyStorage fs(fc);
    char *meta = fs.EncodeMeta();

    TFrequencyStorage fs2(meta);
    bool okay = true;
    for (size_t i = 0; i < ALPHA; i++) {
        okay &= fs[i] == fs2[i];
    }
    delete[] meta;
    return okay;
}

TEST(frequency, empty) {
    TFreqArray freq = {};
    bool okay = MyTest(freq);
    ASSERT_TRUE(okay);
}

TEST(frequency, alphabet) {
    TFreqArray arr = {};
    for (uchar a = 'a'; a <= 'z'; a++) {
        arr[a]++;
    }
    bool okay = MyTest(arr);
    ASSERT_TRUE(okay);
}

TEST(frequency, all) {
    TFreqArray arr = {};
    for (size_t i = 0; i < ALPHA; i++) {
        for (size_t j = 0; j < (i % 5) + 1; j++) {
            arr[i]++;
        }
    }
    bool okay = MyTest(arr);
    ASSERT_TRUE(okay);
}

TEST(frequency, random) {
    TFreqArray arr = {};
    for (size_t i = 0; i < ALPHA; i++) {
        for (int j = 0; j < rand() % 50; j++) {
            arr[i]++;
        }
    }
    bool okay = MyTest(arr);
    ASSERT_TRUE(okay);
}
