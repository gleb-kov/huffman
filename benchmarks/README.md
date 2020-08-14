# Benchmarks

## Test cases

1. Synthetic. Very optimistic test case. [Generator](generators/phrases.py#L7)
2. English text. Simulates using some main constraints. [Generator](generators/phrases.py#L36)
3. Random. Contains letters in both cases, numbers, signs. Simulates log or code source files. [Generator](generators/streamers.py#L3)

## How to run

How to run benchmark:
1. Build console utility
2. ```./run.sh <path to utility binary file> <mode> <test size>```

How to use test generator for manual testing:
1. Go to [generators](generators)
2. ```python3 main.py <mode> <filename> <test size>```

## Results

[My machine processor information](procinfo)

Perfomance on single thread.

<details><summary>1. Synthetic tests</summary>
<p>

| Approx. origin size | Encoded size | Saved space | Encode time (ms) | Encode speed | Decode time (ms) | Decode speed |
| ------------------- | ------------ | ----------- | ---------------- | ------------ | ---------------- | ------------ |
| 10 KiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 100 KiB             | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 1 MiB               | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 10 MiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 100 MiB             | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 1 GiB               | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 10 GiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |

</p>
</details>
<details><summary>2. English text</summary>
<p>

| Approx. origin size | Encoded size | Saved space | Encode time (ms) | Encode speed | Decode time (ms) | Decode speed |
| ------------------- | ------------ | ----------- | ---------------- | ------------ | ---------------- | ------------ |
| 10 KiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 100 KiB             | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 1 MiB               | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 10 MiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 100 MiB             | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 1 GiB               | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 10 GiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |

</p>
</details>

<details><summary>3. Random</summary>
<p>

| Approx. origin size | Encoded size | Saved space | Encode time (ms) | Encode speed | Decode time (ms) | Decode speed |
| ------------------- | ------------ | ----------- | ---------------- | ------------ | ---------------- | ------------ |
| 10 KiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 100 KiB             | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 1 MiB               | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 10 MiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 100 MiB             | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 1 GiB               | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |
| 10 GiB              | TODO         | TODO        | TODO             | TODO         | TODO             | TODO         |

</p>
</details>

