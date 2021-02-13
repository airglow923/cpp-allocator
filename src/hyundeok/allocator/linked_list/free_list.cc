#include "hyundeok/allocator/linked_list/free_list.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/best_fit_search.h"

#include <unistd.h>

namespace hyundeok::allocator::linked_list {

namespace {

struct FreeListRootWrapper {
  FreeListRootWrapper() noexcept
      : root_{.size_ = 0, .next_ = &root_, .used_ = false, .data_ = {0}} {}
  ~FreeListRootWrapper() noexcept { ClearFreeList(); }

  HeapHeader root_;
};

// I don't understand why a variable inside anonymous namespace is not
// considered as a static variable. Even if I move it ouside the namespace and
// declare it as static, the linter still raises an error. Is this a bug?
//
// NOLINTNEXTLINE(readability-identifier-naming)
FreeListRootWrapper kRoot;

auto GetFreeListBeforeBegin() -> HeapHeader* { return &kRoot.root_; }

auto GetFreeListBegin() -> HeapHeader* {
  return GetFreeListBeforeBegin()->next_;
}

} // namespace

auto InsertAfter(HeapHeader* pos, HeapHeader* heap) -> HeapHeader* {
  heap->next_ = pos->next_;
  pos->next_ = heap;

  if (heap->next_ != GetFreeListBeforeBegin()) {
    heap = CoalesceNode(heap->next_, heap);
    pos->next_ = heap;
  }

  return heap;
}

auto InsertFront(HeapHeader* heap) -> HeapHeader* {
  return InsertAfter(GetFreeListBeforeBegin(), heap);
}

auto ReleaseNode(SizeT size) -> HeapHeader* {
  auto* match =
      BestFitSearch(GetFreeListBegin(), GetFreeListBeforeBegin(), size);
  if (match == GetFreeListBeforeBegin())
    return nullptr;
  return SplitHeap(match, size);
}

auto CoalesceNode(HeapHeader* lhs, HeapHeader* rhs) -> HeapHeader* {
  lhs->next_ = lhs < rhs ? GetFreeListBeforeBegin() : rhs->next_;
  lhs->size_ += AllocateSize(rhs->size_);
  return lhs;
}

[[nodiscard]] auto CoalesceNeighbor(HeapHeader* head, HeapHeader* cur)
    -> HeapHeader* {
  // when neighbor is prior to node
  HeapHeader* previous = nullptr;

  if (head->next_ != nullptr) {
    for (; head->next_ != cur; head = head->next_)
      continue;
  }

  // when the head is physically prior to the current node
  if (GetHeapEnd(head) == cur) {
    // combine head with previous heap
    previous = CoalesceNode(head, cur);
  }

  // when the next heap is physically next to the current node
  if (cur->next_ != GetFreeListBeforeBegin() && GetHeapEnd(cur) == cur->next_) {
    // combine node with next heap
    if (previous != nullptr)
      previous = CoalesceNode(previous, previous->next_);
    else
      CoalesceNode(cur, cur->next_);
  }

  return previous != GetFreeListBeforeBegin() ? previous : cur;
}

[[nodiscard]] auto SplitHeap(HeapHeader* node, SizeT size) -> HeapHeader* {
  const auto requested = AllocateSize(size);

  if (node->size_ < requested)
    return GetFreeListBeforeBegin();

  auto* new_heap =
      ConvertPtrToHeapHeader(ConvertPtrToCharPtr(GetHeapEnd(node)) - requested);

  node->size_ -= requested;
  InitializeHeapHeader(new_heap, size);
  new_heap->next_ = node->next_;

  return new_heap;
}

auto EraseAfter(HeapHeader* pos) -> HeapHeader* {
  HeapHeader* tmp = pos->next_;
  pos->next_ = pos->next_->next_;
  return tmp;
}

auto ClearFreeList() -> void {
  SizeT total_size = 0;
  auto* node = GetFreeListBegin();

  // get total size of allocated heap
  total_size += AllocateSize(node->size_);
  for (; node != GetFreeListBeforeBegin(); node = node->next_)
    total_size += AllocateSize(node->size_);

  // move heap pointer to the position before heap allocation
  if (brk(ConvertPtrToCharPtr(node) - total_size) == -1)
    return;

  GetFreeListBeforeBegin()->next_ = GetFreeListBeforeBegin();
}

} // namespace hyundeok::allocator::linked_list
