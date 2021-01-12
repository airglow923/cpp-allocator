#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_ITERATOR_TCC
#define HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_ITERATOR_TCC

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_ITERATOR_H
#include "hyundeok/allocator/linked_list/free_list_iterator.h"
#endif

namespace hyundeok::allocator::linked_list {

template <bool constness>
FreeListIterator<constness>::FreeListIterator() noexcept : node_{} {}

template <bool constness>
FreeListIterator<constness>::FreeListIterator(
    const FreeListIterator<>& other) noexcept
    : node_{other.node_} {}

template <bool constness>
FreeListIterator<constness>::FreeListIterator(Node_ node) noexcept
    : node_{node} {}

template <bool constness>
auto FreeListIterator<constness>::operator*() const noexcept -> reference {
  return *node_;
}

template <bool constness>
auto FreeListIterator<constness>::operator->() const noexcept -> pointer {
  return node_;
}

template <bool constness>
auto FreeListIterator<constness>::operator++() noexcept -> Self_& {
  node_ = node_->next_;
  return *this;
}

template <bool constness>
auto FreeListIterator<constness>::operator++(int) noexcept -> Self_ {
  Self_ tmp{*this};
  node_ = node_->next_;
  return tmp;
}

} // namespace hyundeok::allocator::linked_list

#endif
