#ifndef _UTILS_COLLECTION_STATIC_ARENA_H
#define _UTILS_COLLECTION_STATIC_ARENA_H

#include "../common.h"
#include "sized_allocation.h"

/*
 * A simple implementation of an arena/region allocator with a fixed-size buffer.
 *
 * See https://en.wikipedia.org/wiki/Region-based_memory_management for an overview
 */
typedef struct {
    void *start;
    void *next;
    size_t capacity;
} StaticArena;

/*
 * Create a new StaticArena with a specific capacity.
 * This will also allocate the internal buffer on the heap.
 */
StaticArena static_arena_new(size_t capacity);

/*
 * Create a sized allocation in the provided arena allocator.
 * Will return a dummy/null allocation if the arena is full.
 */
SizedAllocation static_arena_alloc(StaticArena *arena, size_t size);

/*
 * Print raw byte contents of the arena.
 */
void static_arena_print_contents_as_bytes(StaticArena *arena);

/*
 * Deallocate the heap memory of the provided arena.
 */
void static_arena_delete(StaticArena *arena);

#endif /* _UTILS_COLLECTION_STATIC_ARENA_H */
