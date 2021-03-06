#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/sequential/sequential_allocate.h"

#include <unistd.h>

namespace hyundeok::allocator::sequential {

auto SequentialAllocate(SizeT size) -> void* {
  size = AlignHeap(size);

  auto* heap = RequestHeap(size);
  auto*& start = GetHeapStartHeader();
  void* data = nullptr;

  if (heap == nullptr)
    return nullptr;

  heap->size_ = size;
  heap->used_ = true;
  heap->next_ = nullptr;
  data = heap->next_;

  if (start == nullptr) {
    start = heap;
  } else {
    start->next_ = heap;
    start = heap;
  }

  return data;
}

auto SequentialFree(void* ptr) -> int {
  auto* heap_header = GetHeapHeader(ptr);
  heap_header->used_ = false;
  auto result = brk(GetHeapStart());

  if (result != -1)
    GetHeapStartHeader() = static_cast<HeapHeader*>(GetHeapStart());

  return result;
}

} // namespace hyundeok::allocator::sequential
