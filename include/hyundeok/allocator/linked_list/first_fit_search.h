#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FIRST_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FIRST_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/types.h"
#include "hyundeok/allocator/linked_list/default_heap_compare_policy.h"

namespace hyundeok::allocator::linked_list {

[[nodiscard]] auto FirstFitSearch(HeapHeader* begin, HeapHeader* end,
                                  SizeT size, HeapComparePolicy auto compare)
    -> HeapHeader* {
  for (; begin != end; begin = begin->next_) {
    if (compare(begin, size))
      return begin;
  }

  return end;
}

[[nodiscard]] inline auto FirstFitSearch(HeapHeader* begin, HeapHeader* end,
                                         SizeT size) -> HeapHeader* {
  return FirstFitSearch(begin, end, size, DefaultHeapComparePolicy);
}

} // namespace hyundeok::allocator::linked_list

#endif
