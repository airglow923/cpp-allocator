#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/default_heap_compare_policy.h"
#include "hyundeok/allocator/linked_list/first_fit_search.h"

namespace hyundeok::allocator::linked_list {

namespace {

HeapHeader* next_fit_cur = GetSentinelNode();

}

[[nodiscard]] auto NextFitSearch(HeapHeader* begin, HeapHeader* end, SizeT size,
                                 HeapComparePolicy auto compare)
    -> HeapHeader* {
  if (next_fit_cur == GetSentinelNode())
    next_fit_cur = begin;

  auto* fit = FirstFitSearch(next_fit_cur, end, size, compare);

  if (fit != end)
    next_fit_cur = fit;
  else
    next_fit_cur = begin;

  return fit;
}

[[nodiscard]] inline auto NextFitSearch(HeapHeader* begin, HeapHeader* end,
                                        SizeT size) -> HeapHeader* {
  return NextFitSearch(begin, end, size, DefaultHeapComparePolicy);
}

} // namespace hyundeok::allocator::linked_list

#endif
