#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_TYPES_HPP_
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_TYPES_HPP_

#include <cstdint>

namespace hyundeok {
namespace allocator {

using word_t = std::intptr_t;
using size_t = std::size_t;

/*
 * next_ points to the first address of the next heap block.
 * data_ ponits to the first sizeof(intptr_t) bytes of the actual data.
 */
struct HeapHeader {
  size_t size_;
  bool used_;
  HeapHeader* next_;
  void* data_;
};

} // namespace allocator
} // namespace hyundeok

#endif
