# TODO list

## Library
1. Check casts between char and uchar.
4. Check if all counters in size_t.
5. Using perf, measure TBitCode and rewrite with deque of ints if necessary.
6. Using perf, measure constructor of THuffmanTree. Refactor needed.
7. Refactor.
8. Parallel count frequency.
9. Clang-Tidy THuffmanTreeNode ?

## Utility
1. Implement coding buffers.
2. Using buffers, encode and decode.
3. Decode validation, sum in meta == length of decoded
3. Choose buffers constants.
4. Encode directories
5. Check with sanitizers and Valgrind

## Utils
1. Files flags.
2. Contrib.1.
3. Parallel execution

## Config
1. Do something with ALPHA and META_BUFFER_SIZE.

## Contrib
1. move timeutils to contrib, because it's another tools project. 
add contrib header to readme

## Tests
1. Get old tests
2. Write new tests and check coverage

## Organization
1. Write README