#ifndef UTILS_DEFS_H
#define UTILS_DEFS_H

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <limits>

using uchar = unsigned char;
using char8_t = uchar;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using ui8 = uint8_t;
using ui16 = uint16_t;
using ui32 = uint32_t;
using ui64 = uint64_t;

static_assert(sizeof(uchar) == 1);
static_assert(sizeof(size_t) == 8);

namespace NFileUtils {

    std::ifstream OpenInputFile(const char *InFile) noexcept(false);

    std::ofstream OpenOutputFile(const char *OutFile) noexcept(false);

}

namespace NTimeUtils {

    using BENCHMARK_CLOCK = std::chrono::high_resolution_clock;

    template<typename Clock>
    class TStageTimer {
        using TPoint = std::chrono::time_point<Clock>;
        TPoint Snapshot;
    public:
        /* util functions that might be useful and compact */

        static TPoint Now() noexcept {
            return Clock::now();
        }

        template<typename T>
        static auto Duration(TPoint finish, TPoint start) {
            return std::chrono::duration_cast<T>(finish - start);
        }

        template<typename T>
        static auto DurationSince(TPoint point) {
            return Duration<T>(Now(), point);
        }

    public:
        TStageTimer() noexcept {
            StartStage();
        }

        TPoint GetStageStart() const noexcept {
            return Snapshot;
        }

        TPoint StartStage() noexcept {
            Snapshot = Now();
            return Snapshot;
        }

        /* stage is still going, do not update snapshot */
        template<typename T>
        auto GetDuration() const {
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
