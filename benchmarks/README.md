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

| Approx. origin size | Encoded size | Saved, % | Encode time, ms | Decode time, ms |
| ------------------- | ------------ | -------- | --------------- | --------------- |
| 1 KiB               | 2.2 KiB      | -120     | 0               | 0               |
| 5 KiB               | 2.7 KiB      | 46       | 0               | 0               |
| 10 KiB              | 3.3 KiB      | 67       | 0               | 0               |
| 100 KiB             | 15 KiB       | 85       | 0               | 0               |
| 1 MiB               | 130 KiB      | 87       | 5               | 2               |
| 10 MiB              | 1.3 MiB      | 87       | 53              | 24              |
| 100 MiB             | 13 MiB       | 87       | 529             | 233             |

Encode speed: 1.9 MiB per 10 ms.
Decode speed: 4.3 MiB per 10 ms.

</p>
</details>
<details><summary>2. English text</summary>
<p>

| Approx. origin size | Encoded size | Saved, % | Encode time, ms | Decode time, ms |
| ------------------- | ------------ | -------- | --------------- | --------------- |
| 1 KiB               | 2.6 KiB      | -160     | 0               | 0               |
| 5 KiB               | 4.7 KiB      | 6        | 0               | 0               |
| 10 KiB              | 7.3 KiB      | 27       | 0               | 0               |
| 100 KiB             | 55 KiB       | 45       | 1               | 1               |
| 1 MiB               | 542 KiB      | 45       | 15              | 12              |
| 10 MiB              | 5.3 MiB      | 47       | 157             | 128             |
| 100 MiB             | 53 MiB       | 47       | 1574            | 1292            |

Encode speed: 0.6 MiB per 10 ms.
Decode speed: 0.8 MiB per 10 ms.

</p>
</details>

<details><summary>3. Random</summary>
<p>

| Approx. origin size | Encoded size | Saved, % | Encode time, ms | Decode time, ms |
| ------------------- | ------------ | -------- | --------------- | --------------- |
| 1 KiB               | 2.8 KiB      | -180     | 0               | 0               |
| 5 KiB               | 5.9 KiB      | -18      | 0               | 0               |
| 10 KiB              | 9.8 KiB      | 2        | 0               | 0               |
| 100 KiB             | 80 KiB       | 20       | 1               | 1               |
| 1 MiB               | 795 KiB      | 20       | 18              | 15              |
| 10 MiB              | 7.8 MiB      | 22       | 188             | 168             |
| 100 MiB             | 78 MiB       | 22       | 1812            | 1720            |

Encode speed: 0.6 MiB per 10 ms.
Decode speed: 0.6 MiB per 10 ms.

</p>
</details>

