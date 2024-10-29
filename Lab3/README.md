# SSA47 Algorithm

## Overview

The SSA47 algorithm is a custom hashing function designed to generate a 256-bit hash from an input string. The algorithm involves several steps, including finding a prime number, permuting the input string, converting to binary, and mixing bits to produce the final hash.

## Steps

1. **Calculate Number of Bits**: Determine the number of bits in the input string by multiplying its length by 8.
2. **Find Closest Prime**: Find the closest prime number greater than or equal to the number of bits.
3. **Permute Input String**: Permute the input string using the prime number.
4. **Convert to Binary**: Convert the permuted string to a binary string and ensure it is 47 bits long.
5. **Final Permutation**: Permute the binary string using the number of bits.
6. **Mix Bits**: Mix the bits of the final permutation using a custom bit-mixing function.
7. **Convert to Hex**: Convert the mixed bits to a hexadecimal string and ensure it is 64 characters long.
8. **XOR Adjustment**: Adjust the last byte of the hexadecimal string using XOR operations.

## Example Usage

```python
input_string = "test"
hash_result = ssa47(input_string)
print(f"256-bit Hash of '{input_string}': {hash_result}")

input_string = "test."
hash_result = ssa47(input_string)
print(f"256-bit Hash of '{input_string}': {hash_result}")
```

## Functions

- `closeP(n)`: Finds the closest prime number greater than or equal to `n`.
- `permute(input_string, prime)`: Permutes the input string using the prime number.
- `mix_bits(value, rounds=1000)`: Mixes the bits of the value over a specified number of rounds.
- `ssa47(input_string)`: Main function to generate the 256-bit hash from the input string.

## Notes

- The algorithm ensures that the final hash is always 256 bits (64 hexadecimal characters) long.
- The XOR adjustment step ensures that the hash has a consistent format.
