#include <algorithm>
#include <functional>

#include "gtest/gtest.h"
#include "src/library/coding.h"
#include "src/utility/utility.h"

/******************************* Frequency helpers ***************************/

constexpr size_t ALPHA = TFrequencyCounter::ALPHA;
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

/******************************* integration tests ***************************/

const char *InputFile = "test_input.txt";
const char *TempFile = "test_encoded.txt";
const char *OutputFile = "test_output.txt";
size_t Accepted = 0;
size_t Failed = 0;

bool CompareFiles() {
    static const size_t BUF_SIZE = 4096;

    bool status = true;
    std::ifstream lhs(InputFile);
    std::ifstream rhs(OutputFile);
    char buf1[BUF_SIZE], buf2[BUF_SIZE];

    while (lhs && rhs && status) {
        lhs.read(buf1, sizeof(buf1));
        rhs.read(buf2, sizeof(buf2));
        if (lhs.gcount() != rhs.gcount()) {
            status = false;
            break;
        }
        for (size_t i = 0; i < (size_t) lhs.gcount(); i++) {
            status &= (buf1[i] == buf2[i]);
        }
    }
    if ((!lhs && rhs) || (lhs && !rhs)) {
        status = false;
    }
    return status;
}

void OnTestEnd(bool status) {
    if (status) {
        Accepted++;
    } else {
        Failed++;
    }
    std::remove(InputFile);
    std::remove(TempFile);
    std::remove(OutputFile);
}

bool RunTest(const std::function<void(std::ofstream &)> &supplier, bool verbose = true) {
    std::ofstream fout(InputFile);
    supplier(fout);
    fout.close();

    NHuffmanUtility::TBenchStageTimer stageTimer;
    NHuffmanUtility::Compress(InputFile, TempFile, stageTimer, verbose);
    NHuffmanUtility::Decompress(TempFile, OutputFile, stageTimer, verbose);

    bool status = CompareFiles();
    OnTestEnd(status);
    return status;
}

bool RunSmallTest(const std::function<void(std::ofstream &)> &supplier) {
    return RunTest(supplier, false);
}

bool RunMediumTest(const std::function<void(std::ofstream &)> &supplier) {
    return RunTest(supplier, false);
}

/******************************* small tests *********************************/

TEST(full_small, empty) {
    auto supplier = [](std::ofstream &fout) {};
    ASSERT_TRUE(RunSmallTest(supplier));
}

TEST(full_small, one_letter) {
    auto supplier = [](std::ofstream &fout) { fout << "a"; };
    ASSERT_TRUE(RunSmallTest(supplier));
}

TEST(full_small, few_letters) {
    auto supplier = [](std::ofstream &fout) { fout << "abс"; };
    ASSERT_TRUE(RunSmallTest(supplier));
}

TEST(full_small, alphabet) {
    auto supplier = [](std::ofstream &fout) { fout << "abcdefghijklmnopqrstuvwxyz"; };
    ASSERT_TRUE(RunSmallTest(supplier));
}

TEST(full_small, visible) {
    auto supplier = [](std::ofstream &fout) {
        fout << "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        fout << "!\\\\\\\\\\\\\\\"#$%&\\\\\\\\\\\\\\\\'()*+,-./:;<=>?@[\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\]";
        fout << "^_`{|}~ \\\\\\\\\\\\\\\\t\\\\\\\\\\\\\\\\n\\\\\\\\\\\\\\\\r\\\\\\\\\\\\\\\\x0b\\\\\\\\\\\\\\\\x0c";
    };
    ASSERT_TRUE(RunSmallTest(supplier));
}

TEST(full_small, allchars) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 256; i++) {
            fout << (char) (i);
        }
    };
    ASSERT_TRUE(RunSmallTest(supplier));
}

/******************************* medium tests ********************************/

TEST(full_medium, modulo) {
    auto supplier = [](std::ofstream &fout) {
        for (int i = 0; i < 1000; i++) {
            fout << (char) (i % 256);
        }
    };
    ASSERT_TRUE(RunMediumTest(supplier));
}

TEST(full_medium, repeat) {
    auto supplier = [](std::ofstream &fout) {
        for (int i = 0; i < 4097; i++) {
            fout << "aaaa";
        }
    };
    ASSERT_TRUE(RunMediumTest(supplier));
}

TEST(full_medium, alphabet) {
    auto supplier = [](std::ofstream &fout) {
        for (int i = 0; i < 10'000; i++) {
            fout << "abcdefghijklmnopqrstuvwxyz";
        }
    };
    ASSERT_TRUE(RunMediumTest(supplier));
}

TEST(full_medium, pows) {
    auto supplier = [](std::ofstream &fout) {
        for (int i = 0; i < 10'000; i++) {
            fout << "abbbbcccccccccccccccc";
        }
    };
    ASSERT_TRUE(RunMediumTest(supplier));
}

TEST(full_medium, trick_pows) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 20; i++) {
            for (size_t j = 0; j <= (size_t) (1ull << i); j++) {
                fout << (char) (i);
            }
        }
    };
    ASSERT_TRUE(RunMediumTest(supplier));
}

/******************************* large tests *********************************/

TEST(full_large, trick_pows) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 24; i++) {
            for (size_t j = 0; j <= (size_t) (1ull << i); j++) {
                fout << (char) ('a' + i);
            }
        }
    };
    ASSERT_TRUE(RunTest(supplier));
}

TEST(full_large, random) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 100'000'000; i++) {
            fout << (char) (rand() % 256);
        }
    };
    ASSERT_TRUE(RunTest(supplier));
}

TEST(full_large, tree) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 10'000'000; i++) {
            fout << "abbbbcccccccccccccccc";
        }
    };
    ASSERT_TRUE(RunTest(supplier));
}

/******************************* validation tests ****************************/

bool RunValidationTest(const std::function<void(std::ofstream &)> &supplier) {
    std::ofstream fout(TempFile);
    supplier(fout);
    fout.close();

    bool caught = false;
    NHuffmanUtility::TBenchStageTimer stageTimer;
    try {
        NHuffmanUtility::Decompress(TempFile, OutputFile, stageTimer, false);
    } catch (...) {
        caught = true;
    }
    OnTestEnd(caught);
    return caught;
}

TEST(validate, meta) {
    auto supplier = [](std::ofstream &fout) {
        fout << "not enough data as meta";
    };
    ASSERT_TRUE(RunValidationTest(supplier));
}

TEST(validate, length) {
    // length of decoded sequence is checksum
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < TFrequencyStorage::META_BUFFER_SIZE; i++) {
            fout << 1;
        }
        fout << "abc";
    };
    ASSERT_TRUE(RunValidationTest(supplier));
}