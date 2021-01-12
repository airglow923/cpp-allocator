#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H

#include "hyundeok/allocator/concepts.h"
#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list_iterator.h"
#include "hyundeok/allocator/linked_list/first_fit_search.h"

namespace hyundeok::allocator::linked_list {

template <HeapComparePolicy Compare = decltype(&FindMatchHeap),
          HeapSearchPolicy<Compare> Search = FirstFitSearch>
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

  FreeList();

  FreeList(const FreeList&) = delete;

  FreeList(FreeList&& other);

  auto operator=(const FreeList&) -> FreeList& = delete;

  ~FreeList();

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

  auto InsertFront(Node_ heap) -> iterator;

  auto ReleaseNode(SizeT size) -> iterator;

private:
  static auto CoalesceNode(Node_ lhs, Node_ rhs) -> Node_;

  [[nodiscard]] static auto CoalesceNeighbor(const_iterator head,
                                             const_iterator node) -> iterator;

  [[nodiscard]] static auto SplitHeap(const_iterator node, SizeT size)
      -> iterator;

  auto InsertAfter(const_iterator pos, Node_ heap) -> iterator;

  auto EraseAfter(const_iterator pos) -> iterator;

  HeapHeader root_;
  Compare compare_;
  Search search_;
};

} // namespace hyundeok::allocator::linked_list

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_TCC
#include "hyundeok/allocator/linked_list/free_list.tcc"
#endif

#endif
