#ifndef _UTILS_COLLECTION_BIT_VEC32_H
#define _UTILS_COLLECTION_BIT_VEC32_H

#include <stdbool.h>
#include <stdint.h>

/*
 * A 32-bit bit vector that values can be appended to and taken from.
 */
typedef struct {
    uint32_t value;
    uint8_t len;
} BitVec32;

/*
 * Create a new empty bit vector.
 */
BitVec32 bit_vec32_new();

/*
 * Append new bits to the bit vector, with len specifying the number of bits taken from the end of value.
 * 
 * Returns false if this overflows the bit vector.
 */
bool bit_vec32_append(BitVec32 *vec, uint32_t value, uint8_t len);

/*
 * Takes a certain number of bits from the bit vector (specified by len) and saves the result to the
 * value pointed to by out.
 * 
 * Returns false if this overflows the bit vector.
 */
bool bit_vec32_take(BitVec32 *vec, uint32_t *out, uint8_t len);

#endif /* _UTILS_COLLECTION_BIT_VEC32_H */
