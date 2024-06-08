#include "string_view.h"

#include <string.h>

StringView string_view_create(char *ptr, size_t size) {
    StringView view;
    view.ptr = ptr;
    view.size = size;
    return view;
}

void string_view_copy_to(StringView *view, char *buffer) {
    memcpy(buffer, view->ptr, view->size);
}

bool string_view_copy_slice_to(StringView *view, size_t slice_start, size_t slice_end, char *buffer) {
    // Invalid arguments
    if (slice_end < slice_start) {
        return false;
    }

    // The slice has size zero
    if (slice_end == slice_start) {
        return true;
    }

    // Limit maximum value of slice_end to view->size
    if (slice_end > view->size) {
        slice_end = view->size;
    }

    memcpy(buffer, view->ptr + slice_start, slice_end - slice_start);
    return true;
}
