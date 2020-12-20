#include "hyundeok/allocator/linked_list/next_fit_search.h"

namespace hyundeok::allocator::linked_list {

auto GetHeapFit() -> HeapHeader*& {
  static auto* heap_fit = GetHeapStartHeader();
  return heap_fit;
}

auto NextFitSearch(SizeT size) -> HeapHeader* {
  auto* fit = FitSearch(size, GetHeapFit());

  if (fit != nullptr)
    GetHeapFit() = fit;
  else
    GetHeapFit() = GetHeapStartHeader();

  return fit;
}

} // namespace hyundeok::allocator::linked_list
