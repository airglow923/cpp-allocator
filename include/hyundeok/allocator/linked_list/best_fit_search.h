#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_BEST_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok::allocator::linked_list {

template <HeapComparePolicy Compare>
class BestFitSearch {
public:
  auto operator()(HeapHeader* begin, SizeT size) -> HeapHeader* {
    HeapHeader* best = nullptr;

    for (; begin != nullptr; begin = begin->next_) {
      if (compare_(begin, size) &&
          (best == nullptr || begin->size_ < best->size_))
        best = begin;
    }

    return best;
  }

private:
  Compare compare_ = Compare();
};

} // namespace hyundeok::allocator::linked_list

#endif
