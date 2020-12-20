#include "hyundeok/allocator/linked_list/first_fit_search.h"

namespace hyundeok::allocator::linked_list {

auto FirstFitSearch(SizeT size) -> HeapHeader* {
  return FitSearch(size, GetHeapStartHeader());
}

} // namespace hyundeok::allocator::linked_list
