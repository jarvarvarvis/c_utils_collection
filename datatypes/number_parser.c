#include "number_parser.h"

#include <ctype.h>

#define number_parser_return_condition_if_reached_end(condition) \
    if (i >= string_view->size) { *value_len_out = i; return condition; }

#define number_parser_return_len_and_condition_if_reached_end(len, condition) \
    if (i >= string_view->size) { *value_len_out = len; return condition; }

bool number_parser_try_get_len_of_next_int(StringView *string_view, size_t *value_len_out) {
    if (string_view->size == 0) {
        return false;
    }

    size_t i = 0;

    // Check if the value is negative (negative sign at the start)
    if (string_view->ptr[i] == '-') {
        i++;
    }

    // We are already beyond the length of the string, so this can't be a valid value
    number_parser_return_len_and_condition_if_reached_end(0, false);

    // Start parsing whole numbers
    bool starts_with_at_least_one_digit = false;
    while (isdigit(string_view->ptr[i])) {
        starts_with_at_least_one_digit = true;
        i++;

        // If we have parsed at least one digit, this is a valid number
        number_parser_return_condition_if_reached_end(starts_with_at_least_one_digit);
    }

    // If the number doesn't start with at least one digit, it isn't a valid number
    if (!starts_with_at_least_one_digit) {
        return false;
    }

    // The number might have an exponential suffix (but only parse if at least one digit was encountered)
    // Also, if the string ends after the `e`, this can't be a valid exponential suffix
    if (starts_with_at_least_one_digit && string_view->ptr[i] == 'e' && i + 1 < string_view->size) {
        size_t prev_value_of_i = i;
        i++;

        while (isdigit(string_view->ptr[i])) {
            i++;
        }

        // There were no digits behind the `e`, we go back
        if (i == prev_value_of_i + 1) {
            i = prev_value_of_i;
        }
    }

    // Write i to value_len_out, parsing succeeded if i > 0
    *value_len_out = i;
    return i > 0;
}

bool number_parser_try_get_len_of_next_float(StringView *string_view, size_t *value_len_out) {
    if (string_view->size == 0) {
        return false;
    }

    size_t i = 0;

    // Check if the value is negative (negative sign at the start)
    if (string_view->ptr[i] == '-') {
        i++;
    }

    // We are already beyond the length of the string, so this can't be a valid value
    number_parser_return_len_and_condition_if_reached_end(0, false);

    // Start parsing digits at the start
    bool encountered_any_digit_before_exponential_suffix = false;
    while (isdigit(string_view->ptr[i])) {
        encountered_any_digit_before_exponential_suffix = true;
        i++;

        // If we have parsed at least one digit, this is a valid float
        number_parser_return_condition_if_reached_end(encountered_any_digit_before_exponential_suffix);
    }

    // Try parsing the decimal point
    bool encountered_decimal_point = false;
    if (string_view->ptr[i] == '.') {
        encountered_decimal_point = true;
        i++;

        // If we have reached the end here, this is still a valid float
        number_parser_return_condition_if_reached_end(true);
    }

    // Start parsing digits behind the decimal point
    while (isdigit(string_view->ptr[i])) {
        encountered_any_digit_before_exponential_suffix = true;
        i++;

        // If we have reached the end here, this is still a valid float
        number_parser_return_condition_if_reached_end(true);
    }

    // If there were no digits before or after the decimal point, this isn't a valid float.
    if (encountered_decimal_point && !encountered_any_digit_before_exponential_suffix) {
        *value_len_out = 0;
        return false;
    }

    // The number might have an exponential suffix (but only parse if at least one digit was encountered before the exponential)
    // Also, if the string ends after the `e`, this can't be a valid exponential suffix
    if (encountered_any_digit_before_exponential_suffix && string_view->ptr[i] == 'e' && i + 1 < string_view->size) {
        size_t prev_value_of_i = i;
        i++;

        // If we are beyond the length of the string, this isn't a valid float (encountered only the `e`)
        if (i >= string_view->size) {
            *value_len_out = prev_value_of_i;
            return false;
        };

        // If we have not reached the end of the string yet, parse the rest.
        // Negative exponents are supported for floats
        if (string_view->ptr[i] == '-') {
            i++;
        }

        // If we are beyond the length of the string, this isn't a valid float (encountered only a minus sign)
        if (i >= string_view->size) {
            *value_len_out = prev_value_of_i;
            return false;
        }

        // Parse digits
        bool encountered_any_digit_after_exponential_suffix = false;
        while (isdigit(string_view->ptr[i])) {
            encountered_any_digit_after_exponential_suffix = true;
            i++;

            // If any digit was encountered after the minus sign, this is a valid float
            number_parser_return_condition_if_reached_end(encountered_any_digit_after_exponential_suffix);
        }

        // We have only encountered a `-` character, so this isn't a valid exponential.
        // Return to before the `e`
        if (!encountered_any_digit_before_exponential_suffix) {
            i = prev_value_of_i;
        }
    }

    // Write i to value_len_out, parsing succeeded if i > 0
    *value_len_out = i;
    return i > 0;
}
