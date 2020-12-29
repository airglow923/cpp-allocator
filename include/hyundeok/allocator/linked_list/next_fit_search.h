#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_NEXT_FIT_SEARCH_H

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {
namespace linked_list {

auto NextFitSearch(SizeT size) -> HeapHeader*;

}
} // namespace allocator
} // namespace hyundeok

#endif
