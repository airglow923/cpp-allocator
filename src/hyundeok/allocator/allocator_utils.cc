#include "hyundeok/allocator/allocator_utils.h"

#include <unistd.h>

#include <cassert>

namespace hyundeok::allocator {

auto ComputeDataAlignment() -> SizeT { return sizeof(WordT) - sizeof(bool); }

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

auto GetHeapHeader(void* heap) -> HeapHeader* {
  return ConvertPtrToHeapHeader(ConvertPtrToCharPtr(heap) - sizeof(HeapHeader) +
                                ComputeDataAlignment());
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
  return size + sizeof(HeapHeader) - ComputeDataAlignment();
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

auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> void {
  assert(heap != nullptr);

  heap->size_ = size;
  heap->used_ = false;
  heap->next_ = GetSentinelNode();
}

auto FindMatchHeap(HeapHeader* heap, SizeT size) -> bool {
  return !heap->used_ && heap->size_ >= size;
}

auto SplitHeap(HeapHeader* heap, SizeT size) -> HeapHeader* {
  const auto requested = AllocateSize(size);

  if (heap->size_ < requested)
    return nullptr;

  auto* new_heap =
      ConvertPtrToHeapHeader(ConvertPtrToCharPtr(GetHeapEnd(heap)) - requested);
  heap->size_ -= requested;
  InitializeHeapHeader(new_heap, size);
  new_heap->next_ = heap->next_;

  return new_heap;
}

} // namespace hyundeok::allocator
