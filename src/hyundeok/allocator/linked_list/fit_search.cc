#include "hyundeok/allocator/linked_list/fit_search.h"

#include "hyundeok/allocator/allocator_utils.h"

namespace hyundeok::allocator::linked_list {

auto FitSearch(SizeT size, HeapHeader* begin) -> HeapHeader* {
  return FitSearch(size, begin, FindMatchHeap);
}

auto FitSearch(SizeT size, HeapHeader* begin, HeapComparePolicy auto op)
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
