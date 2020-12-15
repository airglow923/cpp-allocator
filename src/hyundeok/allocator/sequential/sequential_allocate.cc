#include "hyundeok/allocator/allocator_commons.h"
#include "hyundeok/allocator/sequential/sequential_allocate.h"

#include <unistd.h>

#include <utility>

namespace hyundeok::allocator::sequential {

namespace {

const void* const heap_start{sbrk(0)};
HeapHeader* top{nullptr};

} // namespace

auto SequentialAllocate(SizeT size) -> void* {
  size = AlignHeap(size);

  auto* heap = RequestHeap(size);
  void* data = nullptr;

  if (heap != nullptr) {
    heap->size_ = size;
    heap->used_ = true;

    if (top != nullptr)
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
auto SequentialFree(void* ptr) -> void {
  // auto* heap_header = GetHeapHeader(ptr);
  // heap_header->used_ = false;
  brk(const_cast<void*>(heap_start));
  // top = GetHeapHeader(const_cast<void*>(heap_start));
}

} // namespace hyundeok::allocator::sequential
