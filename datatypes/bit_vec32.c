#include "bit_vec32.h"

BitVec32 bit_vec32_new() {
    BitVec32 vec;
    vec.value = 0;
    vec.len = 0;
    return vec;
}

bool bit_vec32_append(BitVec32 *vec, uint32_t value, uint8_t len) {
    // Appending too many bits to the bit vector.
    if (vec->len + len >= 32) {
        return false;
    }

    // Let's say we have a bit vector b_32,b_31,...,b_j,...,b_2,b_1 where j = `vec`.len
    //
    // We need to shift the values b_1,...b_j over to the left by `len` bits and then or
    // the first `len` bits of our pushed `value` with the current bit string.

    // 1 << `len` is the bit string 1[0...0], and contains `len` zeroes.
    // If we now subtract 1 from that bit string, we get a value where the first `len` bits are set to 1.
    // That value can be used as a mask for the pushed value.
    uint32_t value_mask = (1 << len) - 1;

    // Create the new value of the bit vector
    vec->value = (vec->value << len) | (value & value_mask);
    vec->len += len;

    return true;
}

bool bit_vec32_take(BitVec32 *vec, uint32_t *out, uint8_t len) {
    // Taking too many bits from end of the vector.
    //
    // We need to be careful here because we are using unsigned ints:
    //     vec->len - len < 0
    // <=> vec->len       < len
    if (vec->len < len) {
        return false;
    }

    // We construct the value mask like in bit_vec32_append and write vec->value (masked with that value) to out.
    uint32_t value_mask = (1 << len) - 1;
    *out = vec->value & value_mask;

    // Then, we need to push vec->value to the right by `len` to remove the last `len` bits.
    vec->value >>= len;

    return true;
}
