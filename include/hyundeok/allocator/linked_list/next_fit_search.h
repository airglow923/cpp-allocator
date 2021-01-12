#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok::allocator::linked_list {

struct NextFitSearch {
  auto operator()(HeapHeader* begin, SizeT size, HeapComparePolicy auto compare)
      -> HeapHeader*;
  HeapHeader* cur_ = nullptr;
};

} // namespace hyundeok::allocator::linked_list

#endif
