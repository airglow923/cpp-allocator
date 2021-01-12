#include "hyundeok/allocator/linked_list/next_fit_search.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

auto NextFitSearch::operator()(HeapHeader* begin, SizeT size,
                               HeapComparePolicy auto compare) -> HeapHeader* {
  if (cur_ == nullptr)
    cur_ = begin;

  auto* fit = FitSearch(cur_, size, compare);

  if (fit != nullptr)
    cur_ = fit;
  else
    cur_ = begin;

  return fit;
}

} // namespace hyundeok::allocator::linked_list
