#include "hyundeok/allocator/allocator_utils.h"

#include <unistd.h>

#include <cassert>
#include <utility>

namespace hyundeok::allocator {

auto GetHeapStart() -> void* {
  static void* const heap_start{sbrk(0)};
  return heap_start;
}

auto GetHeapTop() -> HeapHeader*& {
  static auto* top = static_cast<HeapHeader*>(GetHeapStart());
  return top;
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
    heap = nullptr;

  return heap;
}

auto ConvertPtrToVoidPtr(void* ptr) -> void* { return ptr; }

auto GetHeapHeader(void* heap) -> HeapHeader* {
  return static_cast<HeapHeader*>(ConvertPtrToVoidPtr(
      static_cast<char*>(heap) - sizeof(HeapHeader) + sizeof(WordT)));
}

} // namespace hyundeok::allocator
