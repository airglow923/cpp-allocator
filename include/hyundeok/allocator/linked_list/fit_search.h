#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FIT_SEARCH_H

#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/allocator_utils.h"

namespace hyundeok {
namespace allocator {
namespace linked_list {

auto FitSearch(SizeT size, HeapHeader* begin) -> HeapHeader*;

}
} // namespace allocator
} // namespace hyundeok

#endif
