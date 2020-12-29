#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H

#include "hyundeok/allocator/allocator_types.h"

#if defined(__cpp_concepts) && __cpp_concepts >= 201907L
#include <concepts>
#else
#include <type_traits>
#endif

namespace hyundeok {
namespace allocator {
namespace linked_list {

auto FitSearch(SizeT size, HeapHeader* begin) -> HeapHeader*;

#if defined(__cpp_concepts) && __cpp_concepts >= 201907L
template <std::invocable<HeapHeader*, SizeT> I>
#else
template <typename I>
#endif
auto FitSearch(SizeT size, HeapHeader* begin, I op) -> HeapHeader*;

} // namespace linked_list
} // namespace allocator
} // namespace hyundeok

#endif
