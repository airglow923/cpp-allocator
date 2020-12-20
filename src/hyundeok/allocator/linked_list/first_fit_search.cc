#include "hyundeok/allocator/linked_list/first_fit_search.h"

namespace hyundeok::allocator::linked_list {

auto FirstFitSearch(SizeT size) -> HeapHeader* {
  HeapHeader* fit = nullptr;

  for (auto* heap = static_cast<HeapHeader*>(GetHeapStart()); heap != nullptr;
       heap = heap->next_) {
    if (!heap->used_ && heap->size_ >= size) {
      fit = heap;
      break;
    }
  }

  return fit;
}

} // namespace hyundeok::allocator::linked_list
