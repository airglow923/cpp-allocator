#ifndef _HYUNDEOK_ALLOCATOR_LNKED_LIST_FREE_LIST_H_
#define _HYUNDEOK_ALLOCATOR_LNKED_LIST_FREE_LIST_H_

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {
namespace linked_list {

auto AllocateSize(SizeT size) -> SizeT;
auto ConvertPtrToHeapHeader(void* ptr) -> HeapHeader*;
auto FindMatchHeap(HeapHeader* heap, SizeT size) -> bool;
auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> void;

auto GetHeapStartHeader() -> HeapHeader*&;
auto GetHeapEnd(HeapHeader* heap) -> HeapHeader*;
auto GetSentinelNode() -> HeapHeader*;
auto GetHeapHeader(void* heap) -> HeapHeader*;
auto GetFreeListHead() -> HeapHeader*&;

auto RequestHeap(SizeT size) -> HeapHeader*;
auto AddFreeListNode(HeapHeader* node) -> void;
auto RemoveFreeListNode(HeapHeader* node) -> HeapHeader*;
auto CoalesceNode(HeapHeader* lhs, HeapHeader* rhs) -> HeapHeader*;
auto CoalesceNeighbor(HeapHeader* node) -> HeapHeader*;
auto SplitHeap(HeapHeader* heap, SizeT size) -> HeapHeader*;

}
}
}

#endif
