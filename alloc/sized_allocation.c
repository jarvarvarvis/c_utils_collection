#include "sized_allocation.h"

SizedAllocation sized_allocation_null() {
    SizedAllocation alloc;
    alloc.ptr = NULL;
    alloc.size = 0;
    return alloc;
}
