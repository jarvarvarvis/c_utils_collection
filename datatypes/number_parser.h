#ifndef _UTILS_COLLECTION_NUMBER_PARSER_H
#define _UTILS_COLLECTION_NUMBER_PARSER_H

#include "../common.h"

#include "../datatypes/string_view.h"

bool number_parser_try_get_len_of_next_int(StringView string_view, size_t *value_len_out);
bool number_parser_try_get_len_of_next_float(StringView string_view, size_t *value_len_out);

#endif /* _UTILS_COLLECTION_NUMBER_PARSER_H */
