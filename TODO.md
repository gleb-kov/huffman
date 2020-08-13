# TODO list

## Library
1. Check casts between char and uchar.
2. Check if all counters in size_t.
3. Refactor.
4. Using perf, measure TBitCode and rewrite with deque of ints if necessary.
5. Using perf, measure constructor of THuffmanTree. Refactor needed.

## Utility
1. Decode validation, sum in meta == length of decoded.
2. Refactor + naming.
4. Choose buffers constants.
5. Check with Valgrind.
6. File size in verbose mode.

## Utils
1. move NTimeUtils to contrib, because it's another project. add contrib header to readme.
2. File size.

## Tests
1. Write new tests and check coverage.
2. Fix CMakeLists.

## Organization
1. Write README.
2. non 8-bit chars?
3. dead-code? static analyzer? extra includes? codestyle?

## Benchmarks
2. Write run.sh .
2. Run and fill table.
