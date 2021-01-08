#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_UTILS_H
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_UTILS_H

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {

auto AlignHeap(SizeT n) -> WordT;
auto ComputeDataAlignment() -> SizeT;
auto GetHeapStart() -> void*;
auto ConvertPtrToCharPtr(void* ptr) -> char*;

} // namespace allocator
} // namespace hyundeok

#endif
