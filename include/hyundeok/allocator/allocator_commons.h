#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_COMMONS_H
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_COMMONS_H

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {

auto GetHeapStart() -> void*;
auto GetHeapTop() -> HeapHeader&;
auto AlignHeap(SizeT n) -> WordT;
auto AllocateSize(SizeT size) -> SizeT;
auto RequestHeap(SizeT size) -> HeapHeader*;
auto ConvertPtrToVoidPtr(void* ptr) -> void*;
auto GetHeapHeader(void* heap) -> HeapHeader*;

} // namespace allocator
} // namespace hyundeok

#endif
