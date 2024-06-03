#include "string_list.h"

StringList string_list_new() {
    StringList list;
    LIST_HELPER_INIT_LIST(list, char*, strings, 64);
    return list;
}

void string_list_push(StringList *list, char *str) {
    LIST_HELPER_PUSH_ELEMENT(list, char*, strings, str, 2);
}

void string_list_delete(StringList *list) {
    free(list->strings);
}
