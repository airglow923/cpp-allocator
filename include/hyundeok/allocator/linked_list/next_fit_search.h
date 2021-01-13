#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok::allocator::linked_list {

struct NextFitSearch {
  auto operator()(HeapHeader* begin, SizeT size, HeapComparePolicy auto compare)
      -> HeapHeader* {
    if (cur_ == nullptr)
      cur_ = begin;

    auto* fit = FitSearch(cur_, size, compare);

    if (fit != nullptr)
      cur_ = fit;
    else
      cur_ = begin;

    return fit;
  }

  HeapHeader* cur_ = nullptr;
};

} // namespace hyundeok::allocator::linked_list

#endif
