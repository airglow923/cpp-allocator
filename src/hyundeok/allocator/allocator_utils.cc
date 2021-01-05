#include "hyundeok/allocator/allocator_utils.h"

#include <unistd.h>

#include <cassert>
#include <utility>

namespace hyundeok::allocator {

auto GetHeapStart() -> void* {
  static void* const heap_start = sbrk(0);
  return heap_start;
}

auto GetHeapStartHeader() -> HeapHeader*& {
  static auto* start = GetSentinelNode();
  return start;
}

/**
 * Return an address pointing to one past the end of a given heap.
 */

auto GetHeapEnd(HeapHeader* heap) -> HeapHeader* {
  return ConvertPtrToHeapHeader(ConvertPtrToCharPtr(heap) +
                                AllocateSize(heap->size_));
}

auto GetSentinelNode() -> HeapHeader* {
  static HeapHeader sentinel;
  return &sentinel;
}

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
  assert(size <= kMaxPtrAddress);

  auto* heap = static_cast<HeapHeader*>(sbrk(0));

  if (sbrk(AllocateSize(size)) == reinterpret_cast<void*>(-1))
    return nullptr;

  InitializeHeapHeader(heap, size);

  return heap;
}

// for 1-byte arithmeitc operations on pointer
auto ConvertPtrToCharPtr(void* ptr) -> char* { return static_cast<char*>(ptr); }

auto ConvertPtrToHeapHeader(void* ptr) -> HeapHeader* {
  return static_cast<HeapHeader*>(ptr);
}

auto GetHeapHeader(void* heap) -> HeapHeader* {
  return ConvertPtrToHeapHeader(static_cast<char*>(heap) - sizeof(HeapHeader) +
                                sizeof(WordT));
}

auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> void {
  assert(heap != nullptr);

  heap->size_ = size;
  heap->used_ = false;
  heap->next_ = nullptr;
}

auto FindMatchHeap(HeapHeader* heap, SizeT size) -> bool {
  return !heap->used_ && heap->size_ >= size;
}

auto SplitHeap(HeapHeader* heap, SizeT size) -> HeapHeader* {
  heap->size_ -= AllocateSize(size);
  HeapHeader* new_heap = ConvertPtrToHeapHeader(heap->data_ + heap->size_);
  InitializeHeapHeader(heap, size);
  return new_heap;
}

} // namespace hyundeok::allocator
