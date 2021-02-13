#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_BEST_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/linked_list/default_heap_compare_policy.h"

namespace hyundeok::allocator::linked_list {

[[nodiscard]] auto
BestFitSearch(HeapHeader* begin, HeapHeader* end, SizeT size,
              HeapComparePolicy auto compare = DefaultHeapComparePolicy)
    -> HeapHeader* {
  HeapHeader* best = end;

  for (; begin != end; begin = begin->next_) {
    if ((begin->size_ < best->size_ || best->size_ == 0) &&
        compare(begin, size))
      best = begin;
  }

  return best;
}

[[nodiscard]] inline auto BestFitSearch(HeapHeader* begin, HeapHeader* end,
                                        SizeT size) -> HeapHeader* {
  return BestFitSearch(begin, end, size, DefaultHeapComparePolicy);
}

} // namespace hyundeok::allocator::linked_list

#endif
