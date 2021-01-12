#include "hyundeok/allocator/linked_list/best_fit_search.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

#include <algorithm>

namespace hyundeok::allocator::linked_list {

auto BestFitSearch::operator()(HeapHeader* begin, SizeT size,
                               HeapComparePolicy auto compare) -> HeapHeader* {
  HeapHeader* best = nullptr;

  for (; begin != nullptr; begin = begin->next_) {
    if (compare(begin, size) && (best == nullptr || begin->size_ < best->size_))
      best = begin;
  }

  return best;
}

} // namespace hyundeok::allocator::linked_list
