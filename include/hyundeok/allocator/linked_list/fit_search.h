#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H

#include "hyundeok/allocator/allocator_types.h"

#include <type_traits>

namespace hyundeok {
namespace allocator {
namespace linked_list {

template <typename T>
concept HeapComparePolicy = std::is_invocable_r_v<bool, T, HeapHeader*, SizeT>;

auto FitSearch(SizeT size, HeapHeader* begin) -> HeapHeader*;

auto FitSearch(SizeT size, HeapHeader* begin, HeapComparePolicy auto op)
    -> HeapHeader*;

} // namespace linked_list
} // namespace allocator
} // namespace hyundeok

#endif
