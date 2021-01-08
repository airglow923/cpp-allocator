#include "hyundeok/allocator/linked_list/first_fit_search.h"

#include "hyundeok/allocator/linked_list/free_list.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

auto FirstFitSearch(SizeT size) -> HeapHeader* {
  return FitSearch(GetHeapStartHeader(), size);
}

} // namespace hyundeok::allocator::linked_list
