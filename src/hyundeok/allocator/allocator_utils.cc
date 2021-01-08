#include "hyundeok/allocator/allocator_utils.h"

#include <unistd.h>

#include <cassert>

namespace hyundeok::allocator {

auto ComputeDataAlignment() -> SizeT { return sizeof(WordT) - sizeof(bool); }

auto GetHeapStart() -> void* {
  static void* const heap_start = sbrk(0);
  return heap_start;
}

auto AlignHeap(SizeT n) -> WordT {
  return (n + sizeof(WordT) - 1) & ~(sizeof(WordT) - 1);
}

// for 1-byte arithmeitc operations on pointer
auto ConvertPtrToCharPtr(void* ptr) -> char* { return static_cast<char*>(ptr); }

} // namespace hyundeok::allocator
