#include "hyundeok/allocator/linked_list/first_fit_search.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

auto FirstFitSearch(SizeT size) -> HeapHeader* {
  return FitSearch(size, GetHeapStartHeader());
}

} // namespace hyundeok::allocator::linked_list
