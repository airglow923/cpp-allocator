#ifndef HYUNDEOK_ALLOCATOR_LNKED_LIST_FREE_LIST_ITERATOR_H
#define HYUNDEOK_ALLOCATOR_LNKED_LIST_FREE_LIST_ITERATOR_H

#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/allocator_utils.h"

#include <iterator>    // iterator_traits, forward_iterator_tag
#include <type_traits> // conditional
#include <compare>     // strong_ordering"

namespace hyundeok::allocator::linked_list {

template <bool constness = false>
struct [[maybe_unused]] FreeListIterator {
  // NOLINTNEXTLINE(readability-identifier-naming)
  using Self_ = FreeListIterator;
  // NOLINTNEXTLINE(readability-identifier-naming)
  using Node_ = std::conditional_t<constness, const HeapHeader*, HeapHeader*>;

  // NOLINTNEXTLINE(readability-identifier-naming)
  using difference_type = typename std::iterator_traits<Node_>::difference_type;

  // NOLINTNEXTLINE(readability-identifier-naming)
  using value_type = typename std::iterator_traits<Node_>::value_type;

  // NOLINTNEXTLINE(readability-identifier-naming)
  using pointer = typename std::iterator_traits<Node_>::pointer;

  // NOLINTNEXTLINE(readability-identifier-naming)
  using reference = typename std::iterator_traits<Node_>::reference;

  // NOLINTNEXTLINE(readability-identifier-naming)
  using iterator_category = std::forward_iterator_tag;

  // NOLINTNEXTLINE(readability-identifier-naming)
  using iterator_concept = std::forward_iterator_tag;

  FreeListIterator() noexcept;

  FreeListIterator(const FreeListIterator<>& other) noexcept;

  explicit FreeListIterator(Node_ node) noexcept;

  auto operator*() const noexcept -> reference;

  auto operator->() const noexcept -> pointer;

  auto operator++() noexcept -> Self_&;

  auto operator++(int) noexcept -> Self_;

  auto operator<=>(const Self_& other) const -> std::strong_ordering;

  Node_ node_;
};

} // namespace hyundeok::allocator::linked_list

#ifndef HYUNDEOK_ALLOCATOR_LINKED_LIST_FREE_LIST_ITERATOR_TCC
#include "hyundeok/allocator/linked_list/free_list_iterator.tcc"
#endif

#endif
