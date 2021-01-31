#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list.h"
#include "hyundeok/allocator/linked_list/first_fit_search.h"

namespace hyundeok::allocator::linked_list {

template <typename T, HeapSearchPolicy Search = FirstFitSearch<FindMatchHeap>>
class ListAllocator {
  // NOLINTNEXTLINE(readability-identifier-naming)
  using Self_ = ListAllocator;

public:
  ListAllocator();

private:
  FreeList<Search> freelist_;
};

} // namespace hyundeok::allocator::linked_list

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_TCC
#include "hyundeok/allocator/linked_list/list_allocator.tcc"
#endif

#endif
