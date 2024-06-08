#include "../thirdparty/nft/nft.h"
#include "../datatypes/number_parser.h"

#include <stdbool.h>

nft_suite(number_parser_parse_ints) {
    StringView view_1 = string_view_create("234 end", 3);
    size_t len_1 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(&view_1, &len_1), "Parse basic unsigned integer at start of text");
    nft_assert_eq(len_1, 3, "Parsed unsigned integer of length 3 successfully");

    StringView view_2 = string_view_create("abc 129 stop", 12);
    size_t len_2 = 0;
    nft_assert(!number_parser_try_get_len_of_next_int(&view_2, &len_2), "Try parse basic unsigned integer between words");
    nft_assert_eq(len_2, 0, "Didn't parse unsigned integer between words");

    StringView view_3 = string_view_create("-12378934", 9);
    size_t len_3 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(&view_3, &len_3), "Parse negative integer");
    nft_assert_eq(len_3, 9, "Parsed signed integer of length 9 successfully");

    StringView view_4 = string_view_create("10e4", 4);
    size_t len_4 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(&view_4, &len_4), "Parse integer with exponential suffix");
    nft_assert_eq(len_4, 4, "Parsed integer with exponential suffix");

    StringView view_5 = string_view_create("-15e5", 5);
    size_t len_5 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(&view_5, &len_5), "Parse negative integer with exponential suffix");
    nft_assert_eq(len_5, 5, "Parsed negative integer with exponential suffix");

    StringView view_6 = string_view_create("e12", 3);
    size_t len_6 = 0;
    nft_assert(!number_parser_try_get_len_of_next_int(&view_6, &len_6), "Parse integer with exponential suffix but no digits at start");
    nft_assert_eq(len_6, 0, "Didn't parse exponential suffix for no digits at start");

    StringView view_7 = string_view_create("2e", 2);
    size_t len_7 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(&view_7, &len_7), "Parse integer with exponential suffix but no digits at end");
    nft_assert_eq(len_7, 1, "Didn't parse exponential suffix for no digits at end");

    StringView view_8 = string_view_create("-", 1);
    size_t len_8 = 0;
    nft_assert(!number_parser_try_get_len_of_next_int(&view_8, &len_8), "Parse just negative sign");
    nft_assert_eq(len_8, 0, "Didn't parse just negative sign as number");
}

nft_suite(number_parser_parse_floats) {
    StringView view_1 = string_view_create("234 end", 3);
    size_t len_1 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_1, &len_1), "Implicit int -> float: Parse basic unsigned integer at start of text");
    nft_assert_eq(len_1, 3, "Implicit int -> float: Parsed unsigned integer of length 3 successfully");

    StringView view_2 = string_view_create("abc 129 stop", 12);
    size_t len_2 = 0;
    nft_assert(!number_parser_try_get_len_of_next_float(&view_2, &len_2), "Implicit int -> float: Try parse basic unsigned integer between words");
    nft_assert_eq(len_2, 0, "Implicit int -> float: Didn't parse unsigned integer between words");

    StringView view_3 = string_view_create("-12378934", 9);
    size_t len_3 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_3, &len_3), "Implicit int -> float: Parse negative integer");
    nft_assert_eq(len_3, 9, "Implicit int -> float: Parsed signed integer of length 9 successfully");

    StringView view_4 = string_view_create("10e4", 4);
    size_t len_4 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_4, &len_4), "Implicit int -> float: Parse integer with exponential suffix");
    nft_assert_eq(len_4, 4, "Implicit int -> float: Parsed integer with exponential suffix");

    StringView view_5 = string_view_create("-15e5", 5);
    size_t len_5 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_5, &len_5), "Implicit int -> float: Parse negative integer with exponential suffix");
    nft_assert_eq(len_5, 5, "Implicit int -> float: Parsed negative integer with exponential suffix");

    StringView view_6 = string_view_create("e12", 3);
    size_t len_6 = 0;
    nft_assert(!number_parser_try_get_len_of_next_float(&view_6, &len_6), "Implicit int -> float: Parse integer with exponential suffix but no digits at start");
    nft_assert_eq(len_6, 0, "Implicit int -> float: Didn't parse exponential suffix for no digits at start");

    StringView view_7 = string_view_create("2e", 2);
    size_t len_7 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_7, &len_7), "Implicit int -> float: Parse integer with exponential suffix but no digits at end");
    nft_assert_eq(len_7, 1, "Implicit int -> float: Didn't parse exponential suffix for no digits at end");

    StringView view_8 = string_view_create("0.255", 5);
    size_t len_8 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_8, &len_8), "Parse basic float with one decimal point");
    nft_assert_eq(len_8, 5, "Parsed full basic float with decimal point");

    StringView view_9 = string_view_create("-0.346456", 9);
    size_t len_9 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_9, &len_9), "Parse basic negative float with one decimal point");
    nft_assert_eq(len_9, 9, "Parsed full basic negative float with decimal point");

    StringView view_10 = string_view_create("0.5e10", 6);
    size_t len_10 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_10, &len_10), "Parse exponential float with one decimal point");
    nft_assert_eq(len_10, 6, "Parsed full exponential float with decimal point");

    StringView view_11 = string_view_create("-0.345e-10", 10);
    size_t len_11 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_11, &len_11), "Parse negative float with negative exponential and one decimal point");
    nft_assert_eq(len_11, 10, "Parsed full negative float with negative exponential and one decimal point");

    StringView view_12 = string_view_create(".e-10", 5);
    size_t len_12 = 0;
    nft_assert(!number_parser_try_get_len_of_next_float(&view_12, &len_12), "Parse float with incomplete decimal");
    nft_assert_eq(len_12, 0, "Float with incomplete decimal wasn't parsed at all");

    StringView view_13 = string_view_create("-.23489e-10", 11);
    size_t len_13 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_13, &len_13), "Parse negative float with no digits before decimal point, with negative exponential");
    nft_assert_eq(len_13, 11, "Parsed full negative float with no digits before decimal point, with negative exponential");

    StringView view_14 = string_view_create("-14930.e-10", 11);
    size_t len_14 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_14, &len_14), "Parse negative float with no digits after decimal point, with negative exponential");
    nft_assert_eq(len_14, 11, "Parsed full negative float with no digits after decimal point, with negative exponential");

    StringView view_15 = string_view_create(".255", 4);
    size_t len_15 = 0;
    nft_assert(number_parser_try_get_len_of_next_float(&view_15, &len_15), "Parse basic float with no digits before decimal point");
    nft_assert_eq(len_15, 4, "Parsed full basic float with no digits before decimal point");

    StringView view_16 = string_view_create("1.e-", 4);
    size_t len_16 = 0;
    nft_assert(!number_parser_try_get_len_of_next_float(&view_16, &len_16), "Parse float with incomplete negative exponential");
    nft_assert_eq(len_16, 2, "Parsed only a digit and decimal point of float with incomplete negative exponential");

    StringView view_17 = string_view_create("-", 1);
    size_t len_17 = 0;
    nft_assert(!number_parser_try_get_len_of_next_float(&view_17, &len_17), "Parse just negative sign");
    nft_assert_eq(len_17, 0, "Didn't parse just negative sign as number");
}
