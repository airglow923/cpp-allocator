#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H

#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/allocator_utils.h"

#include <concepts>

namespace hyundeok {
namespace allocator {
namespace linked_list {

auto FitSearch(SizeT size, HeapHeader* begin) -> HeapHeader*;

#if defined(__cpp_lib_concepts)
template <std::invocable<HeapHeader*, SizeT> I>
#else
template <typename I>
#endif
auto FitSearch(SizeT size, HeapHeader* begin, I op) -> HeapHeader*;

} // namespace linked_list
} // namespace allocator
} // namespace hyundeok

#endif
