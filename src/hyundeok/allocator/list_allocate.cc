#include "hyundeok/allocator/list_allocate.h"

#include "hyundeok/allocator/utils.h"
#include "hyundeok/allocator/linked_list/free_list.h"

namespace hyundeok::allocator {

auto ListAllocate(SizeT n) -> void* {
  auto* match = linked_list::ReleaseNode(n);

  if (match != nullptr)
    return match;

  return RequestHeap(n);
}

auto ListDeallocate(HeapHeader* heap) -> void {
  if (heap == nullptr)
    return;

  linked_list::InsertFront(heap);
}

} // namespace hyundeok::allocator
