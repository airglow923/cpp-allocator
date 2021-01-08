#ifndef _HYUNDEOK_ALLOCATOR_LNKED_LIST_FREE_LIST_H_
#define _HYUNDEOK_ALLOCATOR_LNKED_LIST_FREE_LIST_H_

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {
namespace linked_list {

auto GetFreeListHead() -> HeapHeader*&;
auto AddFreeListNode(HeapHeader* node) -> void;
auto RemoveFreeListNode(HeapHeader* node) -> HeapHeader*;
auto CoalesceNode(HeapHeader* lhs, HeapHeader* rhs) -> HeapHeader*;
auto CoalesceNeighbor(HeapHeader* node) -> HeapHeader*;
auto SplitHeap(HeapHeader* heap, SizeT size) -> HeapHeader*;

}
}
}

#endif
