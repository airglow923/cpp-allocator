#include "hyundeok/allocator/linked_list/next_fit_search.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

namespace {

auto GetCurrentHeap() -> HeapHeader*& {
  static HeapHeader* current_heap = nullptr;
  return current_heap;
}

} // namespace

auto NextFitSearch::operator()(SizeT size, HeapComparePolicy auto compare)
    -> HeapHeader* {
  auto*& cur = GetCurrentHeap();
  auto* fit = FitSearch(cur, size, compare);

  if (fit != nullptr)
    cur = fit;
  else
    cur = GetHeapStartHeader();

  return fit;
}

} // namespace hyundeok::allocator::linked_list
