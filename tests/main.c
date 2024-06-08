#include "../thirdparty/nft/nft.h"

#include "number_parser.h"

// Silly hack to provide implementations for c_utils_collection functions - just include all .c files
#include "../alloc/sized_allocation.c"
#include "../alloc/static_arena.c"

#include "../datatypes/bit_vec32.c"
#include "../datatypes/number_parser.c"
#include "../datatypes/string_list.c"
#include "../datatypes/string_view.c"

#include "../os/io.c"

#include "../math.c"


int main() {
    nft_run_suite(number_parser_parse_ints);
    nft_run_suite(number_parser_parse_floats);
    nft_log_final();
}
