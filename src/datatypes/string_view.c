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
