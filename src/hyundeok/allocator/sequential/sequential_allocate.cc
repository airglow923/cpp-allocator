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
  heap->next_ = GetSentinelNode();
  data = heap->next_;

  if (start == GetSentinelNode()) {
    start = heap;
  } else {
    start->next_ = heap;
    start = heap;
  }

  return data;
}

/*
 * The design of deallocation method used here is only for demonstration
 * purpose, not for production. Since sequential allocation mostly relies
 * either on garbage collection or pool allocation, dealocation is not covered
 * here.
 */
auto SequentialFree(void* ptr) -> int {
  auto* heap_header = GetHeapHeader(ptr);
  heap_header->used_ = false;
  auto result = brk(GetHeapStart());

  if (result != -1)
    GetHeapStartHeader() = static_cast<HeapHeader*>(GetHeapStart());

  return result;
}

} // namespace hyundeok::allocator::sequential
