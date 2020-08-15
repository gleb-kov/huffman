#ifndef UTILS_DEFS_H
#define UTILS_DEFS_H

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <limits>
#include <climits>

using uchar = unsigned char;
using char8_t = uchar;
constexpr size_t CHBITS = CHAR_BIT;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using ui8 = uint8_t;
using ui16 = uint16_t;
using ui32 = uint32_t;
using ui64 = uint64_t;

static_assert(CHBITS == 8); // a lot of invariants on this state
static_assert(sizeof(uchar) == 1);
static_assert(sizeof(size_t) == 8);
static_assert(sizeof(char) == sizeof(uchar));

template<typename T>
constexpr T Max = std::numeric_limits<T>::max();

namespace NFileUtils {

    std::ifstream OpenInputFile(const char *inFile) noexcept(false);

    std::ofstream OpenOutputFile(const char *outFile) noexcept(false);

    void SetToBegin(std::ifstream &);
}

namespace NTimeUtils {

    using BENCHMARK_CLOCK = std::chrono::high_resolution_clock;

    template<typename Clock>
    class TStageTimer {
        using TPoint = std::chrono::time_point<Clock>;
        TPoint Snapshot;
        TPoint InitPoint;

    public:
        /* util functions that might be useful and compact */

        [[nodiscard]] static TPoint Now() noexcept {
            return Clock::now();
        }

        template<typename T>
        [[nodiscard]] static auto Duration(TPoint finish, TPoint start) {
            return std::chrono::duration_cast<T>(finish - start);
        }

        template<typename T>
        [[nodiscard]] static auto DurationSince(TPoint point) {
            return Duration<T>(Now(), point);
        }

    public:
        TStageTimer() noexcept {
            InitPoint = StartStage();
        }

        TPoint GetStageStart() const noexcept {
            return Snapshot;
        }

        TPoint StartStage() noexcept {
            Snapshot = Now();
            return Snapshot;
        }

        template<typename T>
        [[nodiscard]] auto SinceInit() const {
            return DurationSince<T>(InitPoint);
        }

        /* stage is still going, do not update snapshot */
        template<typename T>
        [[nodiscard]] auto GetDuration() const {
            return DurationSince<T>(Snapshot);
        }

        /* stop stage and return duration */
        template<typename T>
        auto StopStage() {
            TPoint helper = Now();
            std::swap(helper, Snapshot);
            return Duration<T>(Snapshot, helper);
        }
    };

}

#endif //UTILS_DEFS_H
