#ifndef HUFFMAN_TYPES_H
#define HUFFMAN_TYPES_H

#include <cstdint>
#include <cstddef>

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

#endif //HUFFMAN_TYPES_H
