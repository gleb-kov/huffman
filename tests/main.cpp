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

/******************************* THuffmanTree ********************************/

// TODO

/******************************* integration tests ***************************/

const char *InputFile = "test_input.txt";
const char *TempFile = "test_encoded.txt";
const char *OutputFile = "test_output.txt";
size_t Accepted = 0;
size_t Failed = 0;

bool CompareFiles() {
    bool status = true;

    std::ifstream lhs(InputFile), rhs(OutputFile);

    char buf1[1024], buf2[1024];
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

bool RunTest(const std::function<void(std::ofstream &)> &supplier, bool small) {
    if (!small && Failed) {
        std::cout << "Big test wouldn't be launched due some failure before." << std::endl;
        return true;
    }
    std::ofstream fout(InputFile);
    supplier(fout);
    fout.close();

    NHuffmanUtility::TBenchStageTimer stageTimer;
    NHuffmanUtility::Compress(InputFile, TempFile, stageTimer, true);
    NHuffmanUtility::Decompress(TempFile, OutputFile, stageTimer, true);
    //auto finish = stageTimer.StopStage<std::chrono::milliseconds>();

    bool status = CompareFiles();
    OnTestEnd(status);
    return status;
}

/******************************* small tests *********************************/

TEST(full_small, empty) {
    auto supplier = [](std::ofstream &fout) {};
    ASSERT_TRUE(RunTest(supplier, true));
}

TEST(full_small, one_letter) {
    auto supplier = [](std::ofstream &fout) { fout << "a"; };
    ASSERT_TRUE(RunTest(supplier, true));
}
/*
TEST(full_small, few_letters) {
    auto supplier = [](std::ofstream &fout) { fout << "abc"; };
    ASSERT_TRUE(RunTest(supplier, true));
}

TEST(full_small, alphabet) {
    auto supplier = [](std::ofstream &fout) { fout << "abcdefghijklmnopqrstuvwxyz"; };
    ASSERT_TRUE(RunTest(supplier, true));
}

TEST(full_small, visible) {
    auto supplier = [](std::ofstream &fout) {
        fout << "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        fout << "!\\\\\\\\\\\\\\\"#$%&\\\\\\\\\\\\\\\\'()*+,-./:;<=>?@[\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\]";
        fout << "^_`{|}~ \\\\\\\\\\\\\\\\t\\\\\\\\\\\\\\\\n\\\\\\\\\\\\\\\\r\\\\\\\\\\\\\\\\x0b\\\\\\\\\\\\\\\\x0c";
    };
    ASSERT_TRUE(RunTest(supplier, true));
}*/

/******************************* medium tests ********************************/

/*
TEST(full_medium, modulo) {
    auto supplier = [](std::ofstream &fout) {
        for (int i = 0; i < 1000; i++) {
            fout << (char) (i % 256);
        }
    };
    ASSERT_TRUE(RunTest(supplier, false));
}

TEST(full_medium, repeat) {
    auto supplier = [](std::ofstream &fout) {
        for (int i = 0; i < 1000; i++) {
            fout << "aaaa";
        }
    };
    ASSERT_TRUE(RunTest(supplier, false));
}

TEST(full_medium, alphabet) {
    auto supplier = [](std::ofstream &fout) {
        for (int i = 0; i < 10'000; i++) {
            fout << "abcdefghijklmnopqrstuvwxyz";
        }
    };
    ASSERT_TRUE(RunTest(supplier, false));
}

TEST(full_medium, pows) {
    auto supplier = [](std::ofstream &fout) {
        for (int i = 0; i < 10'000; i++) {
            fout << "abbbbcccccccccccccccc";
        }
    };
    ASSERT_TRUE(RunTest(supplier, false));
}

TEST(full_medium, trick_pows) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 20; i++) {
            for (size_t j = 0; j <= (size_t) (1ull << i); j++) {
                fout << (char) (i);
            }
        }
    };
    ASSERT_TRUE(RunTest(supplier, false));
}*/

/******************************* large tests *********************************/

/*
TEST(full_large, trick_pows) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 24; i++) {
            for (size_t j = 0; j <= (size_t) (1ull << i); j++) {
                fout << (char) (i);
            }
        }
    };
    ASSERT_TRUE(RunTest(supplier, false));
}

TEST(full_medium, random) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 100'000'000; i++) {
            fout << (char) (rand() % 256);
        }
    };
    ASSERT_TRUE(RunTest(supplier, false));
}

TEST(full_medium, tree) {
    auto supplier = [](std::ofstream &fout) {
        for (size_t i = 0; i < 10'000'000; i++) {
            fout << "abbbbcccccccccccccccc";
        }
    };
    ASSERT_TRUE(RunTest(supplier, false));
}
*/

/******************************* validation tests ****************************/

// TODO: check behaviour on wrong encoded file
