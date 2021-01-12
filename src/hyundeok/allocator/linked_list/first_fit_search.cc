#include "hyundeok/allocator/linked_list/first_fit_search.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

auto FirstFitSearch::operator()(SizeT size, HeapComparePolicy auto compare)
    -> HeapHeader* {
  return FitSearch(GetHeapStartHeader(), size, compare);
}

} // namespace hyundeok::allocator::linked_list
