import math

def closeP(n):
    if n < 2:
        return 2
    if n % 2 == 0:
        n += 1
    while True:
        for i in range(3, int(math.sqrt(n)) + 1, 2):
            if n % i == 0:
                break
        else:
            return n
        n += 2

def permute(input_string, prime):
    permuted = ''.join(input_string[(i * prime) % len(input_string)] for i in range(len(input_string)))
    return permuted

def mix_bits(value, rounds=1000):
    for _ in range(rounds):
        value = (value * 47 + 101) & 0xFFFFFFFF
        value ^= (value >> 21)
        value ^= (value << 569) & 0xFFFFFFFF
        value ^= (value >> 839)
    return value

def ssa47(input_string):
    # Step 1:
    num_bits = len(input_string) * 8
    
    # Step 2:
    prime = closeP(num_bits)
    
    # Step 3:
    permstr = permute(input_string, prime)
    
    # Step 4:
    binstr = ''.join(format(ord(c), '08b') for c in permstr)
    if len(binstr) < 47:
        binstr = binstr.zfill(47)
    else:
        binstr = binstr[:47]
    
    # Step 5:
    final_permutation = permute(binstr, num_bits)
    
    # Step 6:
    nperms = math.factorial(num_bits) if num_bits < 21 else 10**6
    mod = [mix_bits(ord(char) % nperms) for char in final_permutation]
    
    # Step 7:
    hexstr = ''.join(format(value, '02x') for value in mod)
    if len(hexstr) > 64:
        hexstr = hexstr[:64]
    elif len(hexstr) < 64:
        hexstr = hexstr.ljust(64, '0')

    # Step 8:
    xor_value = 0
    for i in range(0, len(hexstr), 2):
        xor_value ^= int(hexstr[i:i+2], 16)
    hexstr = hexstr[:62] + format(xor_value, '02x')

    return hexstr

input_string = "test"
hash_result = ssa47(input_string)
print(f"256-bit Hash of '{input_string}': {hash_result}")

input_string = "test."
hash_result = ssa47(input_string)
print(f"256-bit Hash of '{input_string}': {hash_result}")