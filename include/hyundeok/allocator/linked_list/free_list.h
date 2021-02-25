#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H

#include "hyundeok/allocator/types.h"

namespace hyundeok::allocator::linked_list {

auto GetFreeListBegin() -> HeapHeader*;

auto GetFreeListBeforeBegin() -> HeapHeader*;

auto InsertAfter(HeapHeader* pos, HeapHeader* heap) -> HeapHeader*;

auto InsertFront(HeapHeader* heap) -> HeapHeader*;

auto ReleaseNode(SizeT size) -> HeapHeader*;

auto CoalesceNode(HeapHeader* lhs, HeapHeader* rhs) -> HeapHeader*;

[[nodiscard]] auto CoalesceNeighbor(HeapHeader* head, HeapHeader* current)
    -> HeapHeader*;

[[nodiscard]] auto SplitHeap(HeapHeader* node, SizeT size) -> HeapHeader*;

auto EraseAfter(HeapHeader* pos) -> HeapHeader*;

auto ClearFreeList() -> void;

} // namespace hyundeok::allocator::linked_list

#endif
