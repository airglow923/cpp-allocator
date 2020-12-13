#include "hyundeok/allocator/sequential/sequential_allocate.h"

#include <unistd.h>

#include <utility>

namespace hyundeok::allocator::sequential {

namespace {

const HeapHeader* heap_start = nullptr;
HeapHeader* top = nullptr;

auto AlignHeap(SizeT n) -> WordT {
  return (n + sizeof(WordT) - 1) & ~(sizeof(WordT) - 1);
}

/*
 * Why not sizeof(WordT)?
 *
 * Because the size of a variable is not guaranteed to be the same as the size
 * of an array with length 1.
 */
auto AllocateSize(SizeT size) -> SizeT {
  return size + sizeof(HeapHeader) - sizeof(std::declval<HeapHeader>().data_);
}

auto RequestHeap(SizeT size) -> HeapHeader* {
  auto* heap = static_cast<HeapHeader*>(sbrk(0));

  if (sbrk(AllocateSize(size)) == reinterpret_cast<void*>(-1))
    heap = nullptr;

  return heap;
}

auto GetHeapHeader(void* heap) -> HeapHeader* {
  return reinterpret_cast<HeapHeader*>(heap) - sizeof(HeapHeader) +
         sizeof(std::declval<HeapHeader>().data_);
}

} // namespace

auto SequentialAllocate(SizeT size) -> void* {
  size = AlignHeap(size);

  auto* heap = RequestHeap(size);
  heap->size_ = size;
  heap->used_ = true;

  if (heap_start == nullptr)
    heap_start = heap;

  if (top != nullptr)
    top->next_ = heap;

  top = heap;

  return heap->data_;
}

/*
 * The design of deallocation method used here is only for a demonstration
 * purpose, not for production. Since sequential allocation mostly relies
 * either on
 */
auto SequentialFree(void* ptr) -> void {
  auto* heap_header = GetHeapHeader(ptr);
  heap_header->used_ = false;
  // brk(heap_start);
  top = nullptr;
}

} // namespace hyundeok::allocator::sequential
