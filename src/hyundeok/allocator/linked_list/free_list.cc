#include "hyundeok/allocator/linked_list/free_list.h"

#include "hyundeok/allocator/allocator_utils.h"

namespace hyundeok::allocator::linked_list {

auto GetFreeListHead() -> HeapHeader*& {
  static HeapHeader* free_list_head = nullptr;
  return free_list_head;
}

auto AddFreeListNode(HeapHeader* node) -> void {
  auto*& iter = GetFreeListHead();

  if (iter == nullptr) {
    iter = node;
    node->next_ = iter;
    return;
  }

  for (; iter->next_ != nullptr; iter = iter->next_) continue;
  iter = node;
}

auto RemoveFreeListNode(HeapHeader* node) -> void {
  auto*& iter = GetFreeListHead();

  if (iter == nullptr) return;

  if (iter == node) {
    iter = nullptr;
  } else {
    for (; iter->next_ != node; iter = iter->next_) continue;
    iter->next_ = node->next_;
  }
}

} // namespace hyundeok::allocator::linked_list
