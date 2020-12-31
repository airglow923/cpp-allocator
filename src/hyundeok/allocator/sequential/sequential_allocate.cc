#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/sequential/sequential_allocate.h"

#include <unistd.h>

namespace hyundeok::allocator::sequential {

auto SequentialAllocate(SizeT size) -> void* {
  size = AlignHeap(size);

  auto* heap = RequestHeap(size);
  auto*& top = GetHeapTop();
  void* data = nullptr;

  if (heap != nullptr) {
    heap->size_ = size;
    heap->used_ = true;
    top->next_ = heap;
    top = heap;
    data = heap->data_;
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
    GetHeapTop() = GetHeapStartHeader();

  return result;
}

} // namespace hyundeok::allocator::sequential
