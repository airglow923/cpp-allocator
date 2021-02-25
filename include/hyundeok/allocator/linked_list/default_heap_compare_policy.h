#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_DEFAULTHEAPCOMPAREPOLICY_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_DEFAULTHEAPCOMPAREPOLICY_H

#include "hyundeok/allocator/types.h"

namespace hyundeok::allocator::linked_list {

[[nodiscard]] inline auto DefaultHeapComparePolicy(HeapHeader* heap, SizeT size)
    -> bool {
  return !heap->used_ && heap->size_ >= size;
}

} // namespace hyundeok::allocator::linked_list

#endif
