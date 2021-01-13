#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FIRST_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FIRST_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

struct FirstFitSearch {
  auto operator()(HeapHeader* begin, SizeT size, HeapComparePolicy auto compare)
      -> HeapHeader* {
    return FitSearch(begin, size, compare);
  }
};

} // namespace hyundeok::allocator::linked_list

#endif
