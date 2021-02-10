#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_TCC
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_TCC

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_H
#include "hyundeok/allocator/linked_list/free_list.h"
#endif

#include <unistd.h>

#include <cassert>

#define HYUNDEOK_FREELIST_SIG(R)                                               \
  template <HeapSearchPolicy Search>                                           \
  R FreeList<Search>

namespace hyundeok::allocator::linked_list {

namespace {

struct FreeListRootWrapper {
  FreeListRootWrapper() noexcept
      : root_{.size_ = 0, .next_ = nullptr, .used_ = false, .data_ = {0}} {}
  ~FreeListRootWrapper() noexcept {
    SizeT total_size = 0;

    for (auto* node = root_.next_; node != nullptr; node = node->next_)
      total_size += AllocateSize(node->size_);

    brk(ConvertPtrToCharPtr(GetHeapStart()) + total_size);
  }

  HeapHeader root_;
};

FreeListRootWrapper kRoot;

} // namespace

HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::BeforeBegin() noexcept -> iterator {
  return iterator{&kRoot.root_};
}

HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::BeforeBegin() const noexcept
    -> const_iterator {
  return const_iterator{&kRoot.root_};
}

HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::CBeforeBegin() const noexcept
    -> const_iterator {
  return const_iterator{&kRoot.root_};
}

// NOLINTNEXTLINE(readability-make-member-function-const)
HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::begin() noexcept -> iterator {
  return iterator{kRoot.root_.next_};
}

HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::begin() const noexcept
    -> const_iterator {
  return const_iterator{kRoot.root_.next_};
}

HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::cbegin() const noexcept
    -> const_iterator {
  return const_iterator{kRoot.root_.next_};
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::end() noexcept -> iterator {
  return iterator{nullptr};
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::end() const noexcept
    -> const_iterator {
  return const_iterator{nullptr};
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::cend() const noexcept
    -> const_iterator {
  return const_iterator{nullptr};
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG(auto)::InsertAfter(const_iterator pos, Node_ heap)
    -> iterator {
  if (pos == end())
    return end();

  iterator cur{const_cast<Node_>(pos.node_)};
  heap->next_ = cur->next_;
  cur->next_ = heap;
  return iterator{heap};
}

HYUNDEOK_FREELIST_SIG(auto)::InsertFront(Node_ heap) -> iterator {
  auto beg = InsertAfter(CBeforeBegin(), heap);
  if (beg->next_ != nullptr) {
    beg = CoalesceNeighbor(++begin(), beg);
    kRoot.root_.next_ = const_cast<Node_>(beg.node_);
  }
  return begin();
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
HYUNDEOK_FREELIST_SIG(auto)::EraseAfter(const_iterator pos) -> iterator {
  if (pos == end())
    return end();

  iterator cur{const_cast<Node_>(pos.node_)};
  iterator tmp{cur->next_};
  cur->next_ = cur->next_->next_;

  return tmp;
}

HYUNDEOK_FREELIST_SIG(auto)::ReleaseNode(SizeT size) -> iterator {
  auto* match = search_(begin().node_, size);
  return SplitHeap(iterator{match}, size);
}

HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::Empty() const -> bool {
  return kRoot.root_.next_ == nullptr;
}

HYUNDEOK_FREELIST_SIG(auto)::CoalesceNode(Node_ lhs, Node_ rhs) -> Node_ {
  lhs->next_ = lhs < rhs ? nullptr : rhs->next_;
  lhs->size_ += AllocateSize(rhs->size_);
  return lhs;
}

HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::CoalesceNeighbor(
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

HYUNDEOK_FREELIST_SIG([[nodiscard]] auto)::SplitHeap(const_iterator node,
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
