#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_UTILS_H
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_UTILS_H

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {

auto GetHeapStart() -> void*;
auto GetHeapStartHeader() -> HeapHeader*;
auto GetHeapTop() -> HeapHeader*&;
auto AlignHeap(SizeT n) -> WordT;
auto AllocateSize(SizeT size) -> SizeT;
auto RequestHeap(SizeT size) -> HeapHeader*;
auto ConvertPtrToHeapHeader(void* ptr) -> HeapHeader*;
auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> void;
auto GetHeapHeader(void* heap) -> HeapHeader*;
auto SplitHeap(HeapHeader* heap, SizeT size) -> HeapHeader*;

} // namespace allocator
} // namespace hyundeok

#endif
