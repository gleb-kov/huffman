# Huffman coding
This repo contains library and console utility to encode and decode files
using Huffman coding algorithm.

## How to start
Console utility help info: ```./huffman --help```

Example: ```./huffman --compress test.txt out.txt```

[Config file](/src/config.h)

## Performance
[Benchmarks](/benchmarks) with full information and generators.

## Tests
[Tests](/tests) are implemented using [GTest](https://github.com/google/googletest).

## Plans
1. [TODO list with fixes](/TODO.md).
2. Fix space overhead on tiny files 
    (do not encode files less than 1 KiB, 
    spend less bytes for meta information in file begin)
2. Parallel execution.
2. Compressed pattern matching.
3. Work with directories.
