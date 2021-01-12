#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"

#include <type_traits>

namespace hyundeok::allocator::linked_list {

auto FitSearch(HeapHeader* begin, SizeT size, HeapComparePolicy auto op)
    -> HeapHeader*;

} // namespace hyundeok::allocator::linked_list

#endif
