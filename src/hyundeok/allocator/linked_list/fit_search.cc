#include "hyundeok/allocator/linked_list/fit_search.h"

#include "hyundeok/allocator/allocator_utils.h"

namespace hyundeok::allocator::linked_list {

auto FitSearch(HeapHeader* begin, SizeT size) -> HeapHeader* {
  return FitSearch(begin, size, FindMatchHeap);
}

auto FitSearch(HeapHeader* begin, SizeT size, HeapComparePolicy auto op)
    -> HeapHeader* {
  HeapHeader* fit = nullptr;

  for (; begin != nullptr; begin = begin->next_) {
    if (op(begin, size)) {
      fit = begin;
      break;
    }
  }

  return fit;
}

} // namespace hyundeok::allocator::linked_list
