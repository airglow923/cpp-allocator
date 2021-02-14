#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_TCC
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_TCC

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_H
#include "hyundeok/allocator/linked_list/list_allocator.h"
#endif

#define HYUNDEOK_LISTALLOCATOR_TMP                                             \
  template <typename T, HeapSearchPolicy Search>

#define HYUNDEOK_LISTALLOCATOR_CLASS ListAllocator<T, Search>

#define HYUNDEOK_LISTALLOCATOR_SIG(Ret)                                        \
  HYUNDEOK_LISTALLOCATOR_TMP                                                   \
  Ret HYUNDEOK_LISTALLOCATOR_CLASS

namespace hyundeok::allocator::linked_list {

HYUNDEOK_LISTALLOCATOR_SIG(auto)::allocate(size_type n) -> pointer {
  auto* heap = RequestHeap(n);
  freelist_.InsertFront(heap);
  return static_cast<T>(heap);
}

HYUNDEOK_LISTALLOCATOR_SIG(auto)::deallocate(pointer p, size_type n) -> void {}

} // namespace hyundeok::allocator::linked_list

#endif
