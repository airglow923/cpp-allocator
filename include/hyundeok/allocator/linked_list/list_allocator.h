#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list.h"
#include "hyundeok/allocator/linked_list/first_fit_search.h"

#include <memory> // allocator_traits

namespace hyundeok::allocator::linked_list {

template <typename T, HeapSearchPolicy Search = FirstFitSearch<FindMatchHeap>>
class ListAllocator {
  // NOLINTNEXTLINE(readability-identifier-naming)
  using Self_ = ListAllocator;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using trait_type = std::allocator_traits<Self_>;

public:
  // NOLINTNEXTLINE(readability-identifier-naming)
  using value_type = T;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using pointer = typename trait_type::pointer;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using const_pointer = typename trait_type::const_pointer;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using void_pointer = typename trait_type::void_pointer;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using const_void_pointer = typename trait_type::const_void_pointer;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using size_type = typename trait_type::size_type;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using difference_type = typename trait_type::difference_type;

  ListAllocator() = default;

  ListAllocator(const Self_& other) = default;

  auto operator=(const Self_& other) -> Self_& = default;

  template <typename U>
  // NOLINTNEXTLINE(readability-named-parameter)
  ListAllocator(const ListAllocator<U>&) {}

  ~ListAllocator() = default;

  // NOLINTNEXTLINE(readability-identifier-naming)
  auto allocate(size_type n) -> pointer;
  // NOLINTNEXTLINE(readability-identifier-naming)
  auto deallocate(pointer p, size_type n) -> void;

private:
  FreeList<Search> freelist_;
};

} // namespace hyundeok::allocator::linked_list

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_LIST_ALLOCATOR_TCC
#include "hyundeok/allocator/linked_list/list_allocator.tcc"
#endif

#endif
