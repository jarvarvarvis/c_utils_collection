#ifndef _UTILS_COLLECTION_SIZED_ALLOCATION_H
#define _UTILS_COLLECTION_SIZED_ALLOCATION_H

#include "../common.h"

/*
 * Allocated chunk of memory with a pointer and known size.
 */
typedef struct {
    void *ptr;
    size_t size;
} SizedAllocation;

/*
 * Create a zero-sized dummy allocation.
 */
SizedAllocation sized_allocation_null();

#endif /* _UTILS_COLLECTION_SIZED_ALLOCATION_H */
