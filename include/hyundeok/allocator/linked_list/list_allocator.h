#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST / LIST_ALLOCATE_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST / LIST_ALLOCATE_H

#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/linked_list/fit_search.h"

#include <type_traits>

namespace hyundeok {
namespace allocator {
namespace linked_list {

template <typename T>
concept HeapSearchScheme = std::is_invocable_r_v<HeapHeader*, T, SizeT>;

template <typename T, HeapSearchScheme HSS>
class ListAllocator {
public:
  ListAllocator(HeapSearchScheme auto scheme) : scheme_{scheme} {}

private:
  HSS scheme_;
};

} // namespace linked_list
} // namespace allocator
} // namespace hyundeok

#endif
