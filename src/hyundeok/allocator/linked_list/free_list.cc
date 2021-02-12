#include "hyundeok/allocator/linked_list/free_list.h"
#include "hyundeok/allocator/linked_list/best_fit_search.h"

#include <unistd.h>

#include <cassert>

namespace hyundeok::allocator::linked_list {

namespace {

struct FreeListRootWrapper {
  FreeListRootWrapper() noexcept
      : root_{.size_ = 0, .next_ = &root_, .used_ = false, .data_ = {0}} {}
  ~FreeListRootWrapper() noexcept {
    SizeT total_size = 0;

    for (auto* node = root_.next_; node != nullptr; node = node->next_)
      total_size += AllocateSize(node->size_);

    brk(ConvertPtrToCharPtr(GetHeapStart()) + total_size);
  }

  HeapHeader root_;
};

FreeListRootWrapper kRoot;

auto GetFreeListBeforeBegin() -> HeapHeader* { return &kRoot.root_; }

auto GetFreeListBegin() -> HeapHeader* {
  return GetFreeListBeforeBegin()->next_;
}

} // namespace

auto InsertAfter(HeapHeader* pos, HeapHeader* heap) -> HeapHeader* {
  assert(pos != nullptr);

  heap->next_ = pos->next_;
  pos->next_ = heap;
  return heap;
}

auto InsertFront(HeapHeader* heap) -> HeapHeader* {
  auto* beg = InsertAfter(GetFreeListBeforeBegin(), heap);
  if (beg->next_ != GetFreeListBeforeBegin()) {
    beg = CoalesceNeighbor(GetFreeListBegin()->next_, beg);
    kRoot.root_.next_ = beg;
  }
  return GetFreeListBegin();
}

auto EraseAfter(HeapHeader* pos) -> HeapHeader* {
  HeapHeader* tmp = pos->next_;
  pos->next_ = pos->next_->next_;
  return tmp;
}

auto ReleaseNode(SizeT size) -> HeapHeader* {
  auto* match = BestFitSearch(GetFreeListBegin(), size);
  return SplitHeap(match, size);
}

[[nodiscard]] auto Empty() const -> bool {
  return kRoot.root_.next_ == nullptr;
}

auto CoalesceNode(HeapHeader* lhs, HeapHeader* rhs) -> HeapHeader* {
  lhs->next_ = lhs < rhs ? nullptr : rhs->next_;
  lhs->size_ += AllocateSize(rhs->size_);
  return lhs;
}

[[nodiscard]] auto CoalesceNeighbor(HeapHeader* head, HeapHeader* current)
    -> HeapHeader* {
  // when neighbor is prior to node
  auto* iter = const_cast<HeapHeader*>(head.node_);
  auto* cur = const_cast<HeapHeader*>(current.node_);
  HeapHeader* previous = nullptr;

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

  return previous != nullptr ? HeapHeader * {previous} : HeapHeader * {cur};
}

[[nodiscard]] auto SplitHeap(HeapHeader* node, SizeT size) -> HeapHeader* {
  auto* raw_node = const_cast<HeapHeader*>(node.node_);
  const auto requested = AllocateSize(size);

  if (node->size_ < requested)
    return HeapHeader * {nullptr};

  auto* new_heap = ConvertPtrToHeapHeader(
      ConvertPtrToCharPtr(GetHeapEnd(raw_node)) - requested);

  raw_node->size_ -= requested;
  InitializeHeapHeader(new_heap, size);
  new_heap->next_ = node->next_;

  return HeapHeader * {new_heap};
}

} // namespace hyundeok::allocator::linked_list

#endif
