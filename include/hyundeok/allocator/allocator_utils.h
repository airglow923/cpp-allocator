#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_UTILS_H
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_UTILS_H

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {

auto AlignHeap(SizeT n) -> WordT;
auto AllocateSize(SizeT size) -> SizeT;
auto ComputeDataAlignment() -> SizeT;
auto ConvertPtrToCharPtr(void* ptr) -> char*;
auto ConvertPtrToHeapHeader(void* ptr) -> HeapHeader*;
auto FindMatchHeap(HeapHeader* heap, SizeT size) -> bool;
auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> HeapHeader*;
auto GetHeapHeader(void* heap) -> HeapHeader*;
auto GetHeapStart() -> void*;
auto GetHeapStartHeader() -> HeapHeader*&;
auto GetHeapEnd(HeapHeader* heap) -> HeapHeader*;
auto GetSentinelNode() -> HeapHeader*;
auto RequestHeap(SizeT size) -> HeapHeader*;

} // namespace allocator
} // namespace hyundeok

#endif
