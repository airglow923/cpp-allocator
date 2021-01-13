#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_TCC
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_TCC

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H
#include "hyundeok/allocator/linked_list/free_list.h"
#endif

#include <cassert>

#define HYUNDEOK_FREELIST_SIG_(R)                                              \
  template <HeapComparePolicy Compare, HeapSearchPolicy<Compare> Search>       \
  R FreeList<Compare, Search>

namespace hyundeok::allocator::linked_list {

HYUNDEOK_FREELIST_SIG_()::FreeList()
    : root_{.size_ = 0, .next_ = nullptr, .used_ = false, .data_ = {0}},
      compare_{}, search_{} {}

HYUNDEOK_FREELIST_SIG_()::FreeList(Self_&& other)
    : root_{std::move(other.root_)}, compare_{std::move(other.compare_)},
      search_{std::move(other.search_)} {
  other.root_.next_ = nullptr;
}

// NOLINTNEXTLINE(modernize-use-equals-default)
HYUNDEOK_FREELIST_SIG_()::~FreeList() {}

HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::BeforeBegin() noexcept -> iterator {
  return iterator{&root_};
}

HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::BeforeBegin() const noexcept
    -> const_iterator {
  return const_iterator{&root_};
}

HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::CBeforeBegin() const noexcept
    -> const_iterator {
  return const_iterator{&root_};
}

// NOLINTNEXTLINE(readability-make-member-function-const)
HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::begin() noexcept -> iterator {
  return iterator{root_.next_};
}

HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::begin() const noexcept
    -> const_iterator {
  return const_iterator{root_.next_};
}

HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::cbegin() const noexcept
    -> const_iterator {
  return const_iterator{root_.next_};
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::end() noexcept -> iterator {
  return iterator{nullptr};
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::end() const noexcept
    -> const_iterator {
  return const_iterator{nullptr};
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::cend() const noexcept
    -> const_iterator {
  return const_iterator{nullptr};
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG_(auto)::InsertAfter(const_iterator pos, Node_ heap)
    -> iterator {
  if (pos == end())
    return end();

  iterator cur{const_cast<Node_>(pos.node_)};
  heap->next_ = cur->next_;
  cur->next_ = heap;
  return iterator{heap};
}

HYUNDEOK_FREELIST_SIG_(auto)::InsertFront(Node_ heap) -> iterator {
  auto beg = InsertAfter(CBeforeBegin(), heap);
  if (beg->next_ != nullptr) {
    beg = CoalesceNeighbor(++begin(), beg);
    root_.next_ = const_cast<Node_>(beg.node_);
  }
  return begin();
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG_(auto)::EraseAfter(const_iterator pos) -> iterator {
  if (pos == end())
    return end();

  iterator cur{const_cast<Node_>(pos.node_)};
  iterator tmp{cur->next_};
  cur->next_ = cur->next_->next_;

  return tmp;
}

HYUNDEOK_FREELIST_SIG_(auto)::ReleaseNode(SizeT size) -> iterator {
  auto* match = search_(begin().node_, size, compare_);
  return SplitHeap(iterator{match}, size);
}

HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::Empty() const -> bool {
  return root_.next_ == nullptr;
}

HYUNDEOK_FREELIST_SIG_(auto)::CoalesceNode(Node_ lhs, Node_ rhs) -> Node_ {
  lhs->next_ = lhs < rhs ? nullptr : rhs->next_;
  lhs->size_ += AllocateSize(rhs->size_);
  return lhs;
}

HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::CoalesceNeighbor(
    const_iterator head, const_iterator current) -> iterator {
  // when neighbor is prior to node
  auto* iter = const_cast<Node_>(head.node_);
  auto* cur = const_cast<Node_>(current.node_);
  Node_ previous = nullptr;

  assert(iter != nullptr && cur != nullptr);

  if (iter->next_ != nullptr) {
    for (; iter->next_ != cur; iter = iter->next_)
      continue;
  }

  // when the iter is physically prior to the current node
  if (GetHeapEnd(iter) == cur) {
    // combine iter with previous heap
    previous = CoalesceNode(iter, cur);
  }

  // when the next heap is physically next to the current node
  if (cur->next_ != nullptr && GetHeapEnd(cur) == cur->next_) {
    // combine node with next heap
    if (previous != nullptr)
      previous = CoalesceNode(previous, previous->next_);
    else
      CoalesceNode(cur, cur->next_);
  }

  return previous != nullptr ? iterator{previous} : iterator{cur};
}

HYUNDEOK_FREELIST_SIG_([[nodiscard]] auto)::SplitHeap(const_iterator node,
                                                      SizeT size) -> iterator {
  auto* raw_node = const_cast<Node_>(node.node_);
  const auto requested = AllocateSize(size);

  if (node->size_ < requested)
    return iterator{nullptr};

  auto* new_heap = ConvertPtrToHeapHeader(
      ConvertPtrToCharPtr(GetHeapEnd(raw_node)) - requested);

  raw_node->size_ -= requested;
  InitializeHeapHeader(new_heap, size);
  new_heap->next_ = node->next_;

  return iterator{new_heap};
}

} // namespace hyundeok::allocator::linked_list

#endif
