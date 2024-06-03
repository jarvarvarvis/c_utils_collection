#ifndef _UTILS_COLLECTION_STRING_LIST_H
#define _UTILS_COLLECTION_STRING_LIST_H

#include "list_helper.h"

typedef struct {
    LIST_HELPER_STRUCT_MEMBERS(char*, strings);
} StringList;

/*
 * Create a new empty string list.
 */
StringList string_list_new();

/*
 * Add a string to the string list.
 */
void string_list_push(StringList *list, char *str);

/*
 * Delete the string list.
 * If the list contains strings that were allocated on the heap, this function will 
 * *NOT* free them!
 */
void string_list_delete(StringList *list);

#endif /* _UTILS_COLLECTION_STRING_LIST_H */
