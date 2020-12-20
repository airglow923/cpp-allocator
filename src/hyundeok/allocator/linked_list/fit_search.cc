#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

auto FitSearch(SizeT size, HeapHeader* begin) -> HeapHeader* {
  HeapHeader* fit = nullptr;

  for (; begin != nullptr; begin = begin->next_) {
    if (!begin->used_ && begin->size_ >= size) {
      fit = begin;
      break;
    }
  }

  return fit;
}

} // namespace hyundeok::allocator::linked_list
