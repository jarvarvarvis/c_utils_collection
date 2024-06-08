#ifndef _UTILS_COLLECTION_DYNAMIC_ARENA_H
#define _UTILS_COLLECTION_DYNAMIC_ARENA_H

#include "../common.h"
#include "sized_allocation.h"

/*
 * A simple implementation of an arena/region allocator with a dynamically reallocating buffer.
 *
 * See https://en.wikipedia.org/wiki/Region-based_memory_management for an overview
 */
typedef struct {
    void *start;
    void *next;
    size_t capacity;
} DynamicArena;

/*
 * Create a new DynamicArena with a specific initial capacity.
 * This will also allocate the internal buffer on the heap.
 */
DynamicArena dynamic_arena_new(size_t capacity);

/*
 * Create a sized allocation in the provided arena allocator.
 * Will reallocate the internal buffer if the arena is full.
 */
SizedAllocation dynamic_arena_alloc(DynamicArena *arena, size_t size);

/*
 * Print raw byte contents of the arena.
 */
void dynamic_arena_print_contents_as_bytes(DynamicArena *arena);

/*
 * Deallocate the heap memory of the provided arena.
 */
void dynamic_arena_delete(DynamicArena *arena);

#endif /* _UTILS_COLLECTION_DYNAMIC_ARENA_H */
