#ifndef _UTILS_COLLECTION_STRING_VIEW_H
#define _UTILS_COLLECTION_STRING_VIEW_H

#include "../common.h"

typedef struct {
    char *ptr;
    size_t size;
} StringView;

/*
 * Create a new string view from a pointer and a size.
 */
StringView string_view_create(char *ptr, size_t size);

/*
 * Copy the full data referenced by the string view to a new buffer.
 */
void string_view_copy_to(StringView *view, char *buffer);

/*
 * Copy a specific slice of the data referenced by the string view to a new buffer.
 * This slice starts at index `slice_start` (inclusive) and ends at index `slice_end` (exclusive).
 * Thus, slice length = slice_end - slice_start.
 */
bool string_view_copy_slice_to(StringView *view, size_t slice_start, size_t slice_end, char *buffer);

#endif /* _UTILS_COLLECTION_STRING_VIEW_H */
