#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

namespace {

auto FindMatchHeap(HeapHeader* heap, SizeT size) -> bool {
  return !heap->used_ && heap->size_ >= size;
}

} // namespace

auto FitSearch(SizeT size, HeapHeader* begin) -> HeapHeader* {
  return FitSearch(size, begin, FindMatchHeap);
}

#if defined(__cpp_lib_concepts)
template <std::invocable<HeapHeader*, SizeT> I>
#else
template<typename I>
#endif
auto FitSearch(SizeT size, HeapHeader* begin, I op) -> HeapHeader* {
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
