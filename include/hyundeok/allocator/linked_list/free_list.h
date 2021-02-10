#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list_iterator.h"

namespace hyundeok::allocator::linked_list {

template <HeapSearchPolicy Search>
class FreeList {
  // NOLINTNEXTLINE(readability-identifier-naming)
  using Self_ = FreeList;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using Node_ = HeapHeader*;

public:
  // NOLINTNEXTLINE(readability-identifier-naming)
  using iterator = FreeListIterator<>;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using const_iterator = FreeListIterator<true>;

  FreeList() = default;

  ~FreeList() = default;

  [[nodiscard]] auto BeforeBegin() noexcept -> iterator;

  [[nodiscard]] auto BeforeBegin() const noexcept -> const_iterator;

  [[nodiscard]] auto CBeforeBegin() const noexcept -> const_iterator;

  // NOLINTNEXTLINE(readability-identifier-naming)
  [[nodiscard]] auto begin() noexcept -> iterator;

  // NOLINTNEXTLINE(readability-identifier-naming)
  [[nodiscard]] auto begin() const noexcept -> const_iterator;

  // NOLINTNEXTLINE(readability-identifier-naming)
  [[nodiscard]] auto cbegin() const noexcept -> const_iterator;

  // NOLINTNEXTLINE(readability-identifier-naming)
  [[nodiscard]] auto end() noexcept -> iterator;

  // NOLINTNEXTLINE(readability-identifier-naming)
  [[nodiscard]] auto end() const noexcept -> const_iterator;

  // NOLINTNEXTLINE(readability-identifier-naming)
  [[nodiscard]] auto cend() const noexcept -> const_iterator;

  [[nodiscard]] auto Empty() const -> bool;

  auto InsertAfter(const_iterator pos, Node_ heap) -> iterator;

  auto InsertFront(Node_ heap) -> iterator;

  auto ReleaseNode(SizeT size) -> iterator;

private:
  static auto CoalesceNode(Node_ lhs, Node_ rhs) -> Node_;

  [[nodiscard]] static auto CoalesceNeighbor(const_iterator head,
                                             const_iterator current)
      -> iterator;

  [[nodiscard]] static auto SplitHeap(const_iterator node, SizeT size)
      -> iterator;

  auto EraseAfter(const_iterator pos) -> iterator;

  Search search_ = Search();
};

} // namespace hyundeok::allocator::linked_list

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_TCC
#include "hyundeok/allocator/linked_list/free_list.tcc"
#endif

#endif
