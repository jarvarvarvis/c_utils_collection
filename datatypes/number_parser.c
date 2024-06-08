#include "number_parser.h"

#include <ctype.h>

bool number_parser_try_get_len_of_next_int(StringView string_view, size_t *value_len_out) {
    if (string_view.size == 0) {
        return false;
    }

    size_t i = 0;

    // Check if the value is negative (negative sign at the start)
    if (string_view.ptr[i] == '-') {
        i++;
    }

    // Start parsing whole numbers
    bool starts_with_at_least_one_digit = false;
    while (isdigit(string_view.ptr[i])) {
        starts_with_at_least_one_digit = true;
        i++;
    }

    // The number might have an exponential suffix (but only parse if there was )
    if (starts_with_at_least_one_digit && string_view.ptr[i] == 'e') {
        i++;
        size_t prev_value_of_i = i;

        while (isdigit(string_view.ptr[i])) {
            i++;
        }

        // There were no digits behind the `e`, we go back
        if (prev_value_of_i == i) {
            i--;
        }
    }

    // Write i to value_len_out, parsing succeeded if i > 0
    *value_len_out = i;
    return i > 0;
}

bool number_parser_try_get_len_of_next_float(StringView string_view, size_t *value_len_out) {
    if (string_view.size == 0) {
        return false;
    }

    size_t i = 0;

    // Check if the value is negative (negative sign at the start)
    if (string_view.ptr[i] == '-') {
        i++;
    }

    // Start parsing whole numbers
    bool starts_with_at_least_one_digit = false;
    while (isdigit(string_view.ptr[i])) {
        starts_with_at_least_one_digit = true;
        i++;
    }

    // The number might have an exponential suffix (but only parse if there was )
    if (starts_with_at_least_one_digit && string_view.ptr[i] == 'e') {
        i++;
        size_t prev_value_of_i = i;

        while (isdigit(string_view.ptr[i])) {
            i++;
        }

        // There were no digits behind the `e`, we go back
        if (prev_value_of_i == i) {
            i--;
        }
    }

    // Write i to value_len_out, parsing succeeded if i > 0
    *value_len_out = i;
    return i > 0;
}
