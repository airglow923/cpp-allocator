#include "hyundeok/allocator/linked_list/next_fit_search.h"

#include "hyundeok/allocator/linked_list/free_list.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

namespace hyundeok::allocator::linked_list {

namespace {

auto GetHeapFit() -> HeapHeader*& {
  static auto* heap_fit = GetHeapStartHeader();
  return heap_fit;
}

} // namespace

auto NextFitSearch(SizeT size) -> HeapHeader* {
  auto* fit = FitSearch(GetHeapFit(), size);

  if (fit != nullptr)
    GetHeapFit() = fit;
  else
    GetHeapFit() = GetHeapStartHeader();

  return fit;
}

} // namespace hyundeok::allocator::linked_list
