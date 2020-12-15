#include "hyundeok/allocator/sequential/sequential_allocate.h"

#include <unistd.h>

#include <utility>

namespace hyundeok::allocator::sequential {

namespace {

const void* const heap_start{sbrk(0)};
HeapHeader* top{nullptr};

auto AlignHeap(SizeT n) -> WordT {
  return (n + sizeof(WordT) - 1) & ~(sizeof(WordT) - 1);
}

/*
 * Why not sizeof(char)?
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

auto ConvertPtrToVoidPtr(void* ptr) -> void* { return ptr; }

auto GetHeapHeader(void* heap) -> HeapHeader* {
  return static_cast<HeapHeader*>(ConvertPtrToVoidPtr(
      static_cast<char*>(heap) - sizeof(HeapHeader) + sizeof(WordT)));
}

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
