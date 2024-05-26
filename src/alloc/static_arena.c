#include "static_arena.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

StaticArena static_arena_new(size_t capacity) {
    StaticArena arena;

    arena.start = malloc(capacity);
    arena.next = arena.start;
    arena.capacity = capacity;

    return arena;
}

SizedAllocation static_arena_alloc(StaticArena *arena, size_t size) {
    if (arena->next + size >= arena->start + arena->capacity) {
        fprintf(stderr, "Unable to allocate %lu bytes in static arena: out of memory!\n", size);
        return sized_allocation_null();
    }

    // Return pointer to the current next free region
    SizedAllocation alloc;
    alloc.size = size;
    alloc.ptr = arena->next;
    arena->next += size;

    printf("Allocated chunk of size %lu in arena at %p, offset from start: %lu\n", size, arena->start, alloc.ptr - arena->start);

    return alloc;
}

void static_arena_print_contents_as_bytes(StaticArena *arena) {
    printf("address             | content \n");
    printf("--------------------|------------------------------------------\n");
    for (size_t i = 0; i < arena->capacity; ++i) {
        uint8_t *ptr = arena->start + i;

        size_t start_idx = i;
        
        // Try to check if the byte is repeated.
        while (i < arena->capacity) {
            uint8_t *next_ptr = arena->start + i + 1;
            if (*next_ptr != *ptr) break;

            i++;
        }

        if (start_idx == i) {
            printf("%008lu            | %d\n", start_idx, *ptr);
        } else {
            printf("%008lu - %008lu | %d\n",   start_idx, i, *ptr);
        }
    }
}

void static_arena_delete(StaticArena *arena) {
    free(arena->start);
}
