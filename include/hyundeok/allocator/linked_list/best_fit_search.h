#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_BEST_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok::allocator::linked_list {

struct BestFitSearch {
  auto operator()(HeapHeader* begin, SizeT size, HeapComparePolicy auto compare)
      -> HeapHeader* {
    HeapHeader* best = nullptr;

    for (; begin != nullptr; begin = begin->next_) {
      if (compare(begin, size) &&
          (best == nullptr || begin->size_ < best->size_))
        best = begin;
    }

    return best;
  }
};

} // namespace hyundeok::allocator::linked_list

#endif
