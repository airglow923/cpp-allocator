#include "hyundeok/allocator/linked_list/free_list.h"

#include "hyundeok/allocator/allocator_utils.h"

#include <unistd.h>

#include <cassert>

namespace hyundeok::allocator::linked_list {

auto AllocateSize(SizeT size) -> SizeT {
  return size + sizeof(HeapHeader) - ComputeDataAlignment();
}

auto ConvertPtrToHeapHeader(void* ptr) -> HeapHeader* {
  return static_cast<HeapHeader*>(ptr);
}

auto FindMatchHeap(HeapHeader* heap, SizeT size) -> bool {
  return !heap->used_ && heap->size_ >= size;
}

auto InitializeHeapHeader(HeapHeader* heap, SizeT size) -> void {
  assert(heap != nullptr);

  heap->size_ = size;
  heap->used_ = false;
  heap->next_ = GetSentinelNode();
}

auto GetHeapStartHeader() -> HeapHeader*& {
  static auto* start = GetSentinelNode();
  return start;
}

/**
 * Return an address pointing to one past the end of a given heap.
 */
auto GetHeapEnd(HeapHeader* heap) -> HeapHeader* {
  return ConvertPtrToHeapHeader(ConvertPtrToCharPtr(heap) +
                                AllocateSize(heap->size_));
}

auto GetSentinelNode() -> HeapHeader* {
  static HeapHeader sentinel;
  return &sentinel;
}

auto GetHeapHeader(void* heap) -> HeapHeader* {
  return ConvertPtrToHeapHeader(ConvertPtrToCharPtr(heap) - sizeof(HeapHeader) +
                                ComputeDataAlignment());
}

auto GetFreeListHead() -> HeapHeader*& {
  static HeapHeader* free_list_head = GetSentinelNode();
  return free_list_head;
}

auto RequestHeap(SizeT size) -> HeapHeader* {
  assert(size <= kMaxPtrAddress);

  auto* heap = static_cast<HeapHeader*>(sbrk(0));

  if (sbrk(AllocateSize(size)) == reinterpret_cast<void*>(-1))
    return nullptr;

  InitializeHeapHeader(heap, size);

  return heap;
}

auto AddFreeListNode(HeapHeader* node) -> void {
  auto*& head = GetFreeListHead();
  node->next_ = head;

  if (head == nullptr) {
    head = node;
    return;
  }

  // This additional variable prevents the head from being assigned to by
  // the pointer "next_".
  auto* iter = head;

  // If the below for loop uses the reference to head,
  //    head = head->next_;
  // this would make GetFreeListHead() point to head->next_;
  for (; iter->next_ != nullptr; iter = iter->next_)
    continue;
  iter->next_ = node;
}

auto RemoveFreeListNode(HeapHeader* node) -> HeapHeader* {
  auto*& head = GetFreeListHead();
  auto* iter = head;

  assert(head != nullptr && node != nullptr);

  for (; iter->next_ != node; iter = iter->next_) {
    // when iterates through all nodes but could not find node
    if (iter == head)
      return nullptr;
  }

  node->used_ = true;
  iter->next_ = node->next_;

  return iter;
}

auto CoalesceNode(HeapHeader* lhs, HeapHeader* rhs) -> HeapHeader* {
  lhs->next_ = rhs->next_;
  lhs->size_ += AllocateSize(rhs->size_);
  return lhs;
}

auto CoalesceNeighbor(HeapHeader* node) -> HeapHeader* {
  // when neighbor is prior to node
  auto* iter = GetFreeListHead();
  HeapHeader* previous = nullptr;

  assert(iter != nullptr && node != nullptr);

  for (; iter->next_ != node; iter = iter->next_)
    continue;

  // when the previous heap is physically prior to node
  if (GetHeapEnd(iter) == node) {
    // combine node with previous heap
    previous = CoalesceNode(iter, node);
  }

  // when neighbor is next to node
  // when the next heap is physically next to node
  if (GetHeapEnd(node) == node->next_) {
    // combine node with next heap
    if (previous != nullptr)
      previous = CoalesceNode(node, node->next_);
    else
      CoalesceNode(node, node->next_);
  }

  return previous != nullptr ? previous : node;
}

auto SplitHeap(HeapHeader* heap, SizeT size) -> HeapHeader* {
  const auto requested = AllocateSize(size);

  if (heap->size_ < requested)
    return nullptr;

  auto* new_heap =
      ConvertPtrToHeapHeader(ConvertPtrToCharPtr(GetHeapEnd(heap)) - requested);
  heap->size_ -= requested;
  InitializeHeapHeader(new_heap, size);
  new_heap->next_ = heap->next_;

  return new_heap;
}

auto SequentialAllocate(SizeT size) -> void* {
  size = AlignHeap(size);

  auto* heap = RequestHeap(size);
  auto*& start = GetHeapStartHeader();
  void* data = nullptr;

  if (heap == nullptr)
    return nullptr;

  heap->size_ = size;
  heap->used_ = true;
  heap->next_ = GetSentinelNode();
  data = heap->next_;

  if (start == GetSentinelNode()) {
      start = heap;
    } else {
        start->next_ = heap;
        start = heap;
      }

  return data;
}

auto SequentialFree(void* ptr) -> int {
  auto* heap_header = GetHeapHeader(ptr);
  heap_header->used_ = false;
  auto result = brk(GetHeapStart());

  if (result != -1)
    GetHeapStartHeader() = static_cast<HeapHeader*>(GetHeapStart());

  return result;
}

} // namespace hyundeok::allocator::linked_list
