#ifndef _HYUNDEOK_ALLOCATOR_LINKED_LIST_BEST_FIT_SEARCH_H_

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {
namespace linked_list {

auto BestFitSearch(SizeT size) -> HeapHeader*;

}
} // namespace allocator
} // namespace hyundeok

#endif
