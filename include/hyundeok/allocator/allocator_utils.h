#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_UTILS_H
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_UTILS_H

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {

auto ComputeDataAlignment() -> SizeT;
auto GetHeapStart() -> void*;
auto GetHeapStartHeader() -> HeapHeader*&;
auto GetHeapEnd(HeapHeader* heap) -> HeapHeader*;
auto GetSentinelNode() -> HeapHeader*;
auto GetHeapHeader(void* heap) -> HeapHeader*;
auto AlignHeap(SizeT n) -> WordT;
auto AllocateSize(SizeT size) -> SizeT;
auto RequestHeap(SizeT size) -> HeapHeader*;
auto ConvertPtrToCharPtr(void* ptr) -> char*;
auto ConvertPtrToHeapHeader(void* ptr) -> HeapHeader*;
auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> void;
auto FindMatchHeap(HeapHeader* heap, SizeT size) -> bool;
auto SplitHeap(HeapHeader* heap, SizeT size) -> HeapHeader*;

} // namespace allocator
} // namespace hyundeok

#endif
