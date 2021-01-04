#include "hyundeok/allocator/linked_list/free_list.h"

#include "hyundeok/allocator/allocator_utils.h"

#include <cassert>

namespace hyundeok::allocator::linked_list {

auto GetFreeListHead() -> HeapHeader*& {
  static HeapHeader* free_list_head = nullptr;
  return free_list_head;
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
  for (; iter->next_ != nullptr; iter = iter->next_) continue;
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

} // namespace hyundeok::allocator::linked_list
