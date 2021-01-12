#include "hyundeok/allocator/allocator_utils.h"

#include <unistd.h>

#include <cassert>

namespace hyundeok::allocator {

auto AlignHeap(SizeT n) -> WordT {
  return (n + sizeof(WordT) - 1) & ~(sizeof(WordT) - 1);
}

auto AllocateSize(SizeT size) -> SizeT {
  return size + sizeof(HeapHeader) - ComputeDataAlignment();
}

auto ComputeDataAlignment() -> SizeT { return sizeof(WordT) - sizeof(bool); }

// for 1-byte arithmeitc operations on pointer
auto ConvertPtrToCharPtr(void* ptr) -> char* { return static_cast<char*>(ptr); }

auto ConvertPtrToHeapHeader(void* ptr) -> HeapHeader* {
  return static_cast<HeapHeader*>(ptr);
}

auto FindMatchHeap(HeapHeader* heap, SizeT size) -> bool {
  return !heap->used_ && heap->size_ >= size;
}

auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> HeapHeader* {
  assert(heap != nullptr);

  heap->size_ = size;
  heap->used_ = false;
  heap->next_ = GetSentinelNode();

  return heap;
}

auto GetHeapHeader(void* heap) -> HeapHeader* {
  return ConvertPtrToHeapHeader(ConvertPtrToCharPtr(heap) - sizeof(HeapHeader) +
                                ComputeDataAlignment());
}

auto GetHeapStart() -> void* {
  static void* const kHeapStart = sbrk(0);
  return kHeapStart;
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
  static HeapHeader sentinel{
      .size_ = 0, .next_ = &sentinel, .used_ = false, .data_ = {0}};
  return &sentinel;
}

auto RequestHeap(SizeT size) -> HeapHeader* {
  assert(size <= kMaxPtrAddress);

  auto* heap = static_cast<HeapHeader*>(sbrk(0));

  if (sbrk(AllocateSize(size)) == reinterpret_cast<void*>(-1))
    return nullptr;

  return InitializeHeapHeader(heap, size);
}

} // namespace hyundeok::allocator
