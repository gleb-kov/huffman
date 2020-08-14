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

| Approx. origin size | Encoded size | Saved, % | Encode time, ms | Encode speed | Decode time, ms | Decode speed |
| ------------------- | ------------ | -------- | --------------- | ------------ | --------------- | ------------ |
| 1 KiB               | 2.2 KiB      | -120     | TODO            | TODO         | TODO            | TODO         |
| 5 KiB               | 2.7 KiB      | 46       | TODO            | TODO         | TODO            | TODO         |
| 10 KiB              | 3.3 KiB      | 67       | TODO            | TODO         | TODO            | TODO         |
| 100 KiB             | 15 KiB       | 85       | TODO            | TODO         | TODO            | TODO         |
| 1 MiB               | 130 KiB      | 87       | TODO            | TODO         | TODO            | TODO         |
| 10 MiB              | 1.3 MiB      | 87       | TODO            | TODO         | TODO            | TODO         |
| 100 MiB             | 13 MiB       | 87       | TODO            | TODO         | TODO            | TODO         |

</p>
</details>
<details><summary>2. English text</summary>
<p>

| Approx. origin size | Encoded size | Saved, % | Encode time, ms | Encode speed | Decode time, ms | Decode speed |
| ------------------- | ------------ | -------- | --------------- | ------------ | --------------- | ------------ |
| 1 KiB               | 2.6 KiB      | -160     | TODO            | TODO         | TODO            | TODO         |
| 5 KiB               | 4.7 KiB      | 6        | TODO            | TODO         | TODO            | TODO         |
| 10 KiB              | 7.3 KiB      | 27       | TODO            | TODO         | TODO            | TODO         |
| 100 KiB             | 55 KiB       | 45       | TODO            | TODO         | TODO            | TODO         |
| 1 MiB               | 542 KiB      | 45       | TODO            | TODO         | TODO            | TODO         |
| 10 MiB              | 5.3 MiB      | 47       | TODO            | TODO         | TODO            | TODO         |
| 100 MiB             | 53 MiB       | 47       | TODO            | TODO         | TODO            | TODO         |

</p>
</details>

<details><summary>3. Random</summary>
<p>

| Approx. origin size | Encoded size | Saved, % | Encode time, ms | Encode speed | Decode time, ms | Decode speed |
| ------------------- | ------------ | -------- | --------------- | ------------ | --------------- | ------------ |
| 1 KiB               | 2.8 KiB      | -180     | TODO            | TODO         | TODO            | TODO         |
| 5 KiB               | 5.9 KiB      | -18      | TODO            | TODO         | TODO            | TODO         |
| 10 KiB              | 9.8 KiB      | 2        | TODO            | TODO         | TODO            | TODO         |
| 100 KiB             | 80 KiB       | 20       | TODO            | TODO         | TODO            | TODO         |
| 1 MiB               | 795 KiB      | 20       | TODO            | TODO         | TODO            | TODO         |
| 10 MiB              | 7.8 MiB      | 22       | TODO            | TODO         | TODO            | TODO         |
| 100 MiB             | 78 MiB       | 22       | TODO            | TODO         | TODO            | TODO         |

</p>
</details>

