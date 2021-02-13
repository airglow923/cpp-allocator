#ifndef HYUNDEOK_ALLOCATOR_LIST_ALLOCATE_H
#define HYUNDEOK_ALLOCATOR_LIST_ALLOCATE_H

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok::allocator {

auto ListAllocate(SizeT n) -> void*;

auto ListDeallocate(HeapHeader* heap) -> void;

}

#endif
