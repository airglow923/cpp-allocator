#include "hyundeok/allocator/linked_list/free_list.h"

#include "hyundeok/allocator/allocator_utils.h"

namespace hyundeok::allocator::linked_list {

auto GetFreeListHead() -> HeapHeader*& {
  static HeapHeader* free_list_head = nullptr;
  return free_list_head;
}

auto AddFreeListNode(HeapHeader* node) -> void {
  auto*& head = GetFreeListHead();

  if (head == nullptr) {
    head = node;
    node->next_ = head;
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

auto RemoveFreeListNode(HeapHeader* node) -> void {
  auto*& head = GetFreeListHead();

  if (head == nullptr) return;

  if (head == node) {
    head = head->next_;
  } else {
    auto* iter = head;
    for (; iter->next_ != node; iter = iter->next_) continue;
    iter->next_ = node->next_;
  }
}

} // namespace hyundeok::allocator::linked_list
