#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/linked_list/default_heap_compare_policy.h"
#include "hyundeok/allocator/linked_list/first_fit_search.h"

namespace hyundeok::allocator::linked_list {

[[nodiscard]] auto NextFitSearch(HeapHeader* begin, HeapHeader* end, SizeT size,
                                 HeapComparePolicy auto compare)
    -> HeapHeader* {
  static auto* kCurNode = begin;

  auto* fit = FirstFitSearch(kCurNode, end, size, compare);

  if (fit != end)
    kCurNode = fit;
  else
    kCurNode = begin;

  return fit;
}

[[nodiscard]] inline auto NextFitSearch(HeapHeader* begin, HeapHeader* end,
                                        SizeT size) -> HeapHeader* {
  return NextFitSearch(begin, end, size, DefaultHeapComparePolicy);
}

} // namespace hyundeok::allocator::linked_list

#endif
