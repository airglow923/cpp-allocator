#include "hyundeok/allocator/utils.h"

#include <unistd.h>

#include <cassert>

namespace hyundeok::allocator {

auto AlignHeap(SizeT n) -> WordT {
  return (n + sizeof(WordT) - 1) & ~(sizeof(WordT) - 1);
}

auto AllocateSize(SizeT size) -> SizeT {
  return size + sizeof(HeapHeader) - ComputeDataAlignment();
}

/**
 * This is because of how the data members of HeapHeader are ordered.
 *
 * used_ in HeapHeader occupies sizeof(bool) byte followed by actual data
 * portion of a heap chunk.
 *
 * Why not simply 1 instead of sizeof(bool)?
 *
 * The size of bool is implementation-defined although many compilers define
 * it as 1.
 */
auto ComputeDataAlignment() -> SizeT { return sizeof(WordT) - sizeof(bool); }

/**
 * This is for 1-byte arithmeitc operations on pointer
 *
 * static_cast<char*> alone cannot do its job because this function is intended
 * to operate on any pointer by converting a pointer to void pointer at first.
 */
auto ConvertPtrToCharPtr(void* ptr) -> char* { return static_cast<char*>(ptr); }

auto ConvertPtrToHeapHeader(void* ptr) -> HeapHeader* {
  return static_cast<HeapHeader*>(ptr);
}

auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> HeapHeader* {
  assert(heap != nullptr);

  heap->size_ = size;
  heap->next_ = nullptr;
  heap->used_ = false;

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
  static auto* kStart = static_cast<HeapHeader*>(GetHeapStart());
  return kStart;
}

/**
 * Return an address pointing to one past the end of a given heap.
 */
auto GetHeapEnd(HeapHeader* heap) -> HeapHeader* {
  return ConvertPtrToHeapHeader(ConvertPtrToCharPtr(heap) +
                                AllocateSize(heap->size_));
}

auto RequestHeap(SizeT size) -> HeapHeader* {
  assert(size <= kMaxPtrAddress);

  auto* heap = static_cast<HeapHeader*>(sbrk(0));

  if (sbrk(AllocateSize(size)) == reinterpret_cast<void*>(-1))
    return nullptr;

  return InitializeHeapHeader(heap, size);
}

} // namespace hyundeok::allocator
