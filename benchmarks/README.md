# Benchmarks

## Test cases

1. Synthetic. Very optimistic test case. [Generator](generators/gen.py#L7)
2. English text. Simulates using some main constraints. [Generator](generators/gen.py#L36)
3. Random. Contains letters in both cases, numbers, signs, line delimiters.
    Simulates log or code source files. [Generator](generators/gen.py#L67)

## How to run

How to run benchmark:

```./run.sh <path to utility binary file> <mode> <test size>``` 
    (path to console utility binary file)

How to use test generator for manual testing:

```python3 generators/main.py <mode> <filename> <test size>```

## Results

[My machine processor information](procinfo)

Performance on single thread.

<details><summary>1. Synthetic tests</summary>
<p>

| Origin size | Encoded size | Saved, % |
| ----------- | ------------ | -------- |
| 1 KiB       | 2.2 KiB      | -120     |
| 5 KiB       | 2.7 KiB      | 46       |
| 10 KiB      | 3.3 KiB      | 67       |
| 100 KiB     | 15 KiB       | 85       |
| 1 MiB       | 130 KiB      | 87       |
| 100 MiB     | 13 MiB       | 87       |

Encode speed: 240.3 MiB / sec.

Decode speed: 452.5 MiB / sec.

</p>
</details>
<details><summary>2. English text</summary>
<p>

| Origin size | Encoded size | Saved, % |
| ----------- | ------------ | -------- |
| 1 KiB       | 2.6 KiB      | -160     |
| 5 KiB       | 4.7 KiB      | 6        |
| 10 KiB      | 7.3 KiB      | 27       |
| 100 KiB     | 55 KiB       | 45       |
| 1 MiB       | 542 KiB      | 45       |
| 100 MiB     | 53 MiB       | 47       |

Encode speed: 71.1 MiB / sec.

Decode speed: 82.2 MiB / sec.

</p>
</details>

<details><summary>3. Random</summary>
<p>

| Origin size | Encoded size | Saved, % |
| ----------- | ------------ | -------- |
| 1 KiB       | 2.8 KiB      | -180     |
| 5 KiB       | 5.8 KiB      | -16      |
| 10 KiB      | 9.5 KiB      | 5        |
| 100 KiB     | 77 KiB       | 23       |
| 1 MiB       | 767 KiB      | 23       |
| 100 MiB     | 75 MiB       | 25       |

Encode speed: 59.6 MiB / sec.

Decode speed: 67.4 MiB / sec.

</p>
</details>
