#include "dynamic_arena.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

DynamicArena dynamic_arena_new(size_t capacity) {
    DynamicArena arena;

    arena.start = malloc(capacity);
    arena.next = arena.start;
    arena.capacity = capacity;

    return arena;
}

SizedAllocation dynamic_arena_alloc(DynamicArena *arena, size_t size) {
    // Dynamically reallocate the buffer if the arena is full
    if (arena->next + size >= arena->start + arena->capacity) {
        arena->capacity *= 2;
        arena->start = realloc(arena->start, arena->capacity);
    }

    // Return pointer to the current next free region
    SizedAllocation alloc;
    alloc.size = size;
    alloc.ptr = arena->next;
    arena->next += size;

    return alloc;
}

void dynamic_arena_print_contents_as_bytes(DynamicArena *arena) {
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

void dynamic_arena_delete(DynamicArena *arena) {
    free(arena->start);
}
