#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H

#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list_iterator.h"

namespace hyundeok::allocator::linked_list {

auto InsertAfter(const_iterator pos, Node_ heap) -> iterator;

auto InsertFront(Node_ heap) -> iterator;

auto ReleaseNode(SizeT size) -> iterator;

auto CoalesceNode(Node_ lhs, Node_ rhs) -> Node_;

[[nodiscard]] auto CoalesceNeighbor(const_iterator head, const_iterator current)
    -> iterator;

[[nodiscard]] auto SplitHeap(const_iterator node, SizeT size) -> iterator;

auto EraseAfter(const_iterator pos) -> iterator;

} // namespace hyundeok::allocator::linked_list

#endif
