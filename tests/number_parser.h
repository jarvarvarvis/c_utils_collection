#include "../thirdparty/nft/nft.h"
#include "../datatypes/number_parser.h"

#include <stdbool.h>

nft_suite(number_parser_parse_ints) {
    StringView view_1 = string_view_create("234 end", 3);
    size_t len_1 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(view_1, &len_1), "Parse basic unsigned integer at start of text");
    nft_assert_eq(len_1, 3, "Parsed unsigned integer of length 3 successfully");

    StringView view_2 = string_view_create("abc 129 stop", 12);
    size_t len_2 = 0;
    nft_assert(!number_parser_try_get_len_of_next_int(view_2, &len_2), "Try parse basic unsigned integer between words");
    nft_assert_eq(len_2, 0, "Didn't parse unsigned integer between words");

    StringView view_3 = string_view_create("-12378934", 9);
    size_t len_3 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(view_3, &len_3), "Parse negative integer");
    nft_assert_eq(len_3, 9, "Parsed signed integer of length 9 successfully");

    StringView view_4 = string_view_create("10e4", 4);
    size_t len_4 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(view_4, &len_4), "Parse integer with exponential suffix");
    nft_assert_eq(len_4, 4, "Parsed integer with exponential suffix");

    StringView view_5 = string_view_create("-15e5", 5);
    size_t len_5 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(view_5, &len_5), "Parse negative integer with exponential suffix");
    nft_assert_eq(len_5, 5, "Parsed negative integer with exponential suffix");

    StringView view_6 = string_view_create("e12", 3);
    size_t len_6 = 0;
    nft_assert(!number_parser_try_get_len_of_next_int(view_6, &len_6), "Parse integer with exponential suffix but no digits at start");
    nft_assert_eq(len_6, 0, "Didn't parse exponential suffix for no digits at start");

    StringView view_7 = string_view_create("2e", 2);
    size_t len_7 = 0;
    nft_assert(number_parser_try_get_len_of_next_int(view_7, &len_7), "Parse integer with exponential suffix but no digits at end");
    nft_assert_eq(len_7, 1, "Didn't parse exponential suffix for no digits at end");
}
