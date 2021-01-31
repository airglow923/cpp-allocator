#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok::allocator::linked_list {

template <HeapComparePolicy Compare>
class NextFitSearch {
public:
  auto operator()(HeapHeader* begin, SizeT size) -> HeapHeader* {
    if (cur_ == nullptr)
      cur_ = begin;

    auto* fit = FitSearch(cur_, size, compare_);

    if (fit != nullptr)
      cur_ = fit;
    else
      cur_ = begin;

    return fit;
  }

private:
  HeapHeader* cur_ = nullptr;
  Compare compare_ = Compare();
};

} // namespace hyundeok::allocator::linked_list

#endif
