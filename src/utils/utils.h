#ifndef UTILS_DEFS_H
#define UTILS_DEFS_H

#include <cstddef>
#include <cstdint>
#include <fstream>

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

#endif //UTILS_DEFS_H