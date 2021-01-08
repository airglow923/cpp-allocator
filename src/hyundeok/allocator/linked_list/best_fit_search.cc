#include "hyundeok/allocator/linked_list/best_fit_search.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

#include <algorithm>

namespace hyundeok::allocator::linked_list {

auto BestFitSearch(SizeT size) -> HeapHeader* {
  HeapHeader* begin = GetHeapStartHeader();
  HeapHeader* best = nullptr;

  for (; begin != nullptr; begin = begin->next_) {
    if (begin->size_ >= size && (best == nullptr || begin->size_ < best->size_))
      best = begin;
  }

  return best;
}

} // namespace hyundeok::allocator::linked_list
