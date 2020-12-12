#pragma once

#ifndef __HYUNDEOK_MEMORY_ALLOCATOR_MEMORY_TYPES_HPP__
#define __HYUNDEOK_MEMORY_ALLOCATOR_MEMORY_TYPES_HPP__

#include <cstdint>

namespace hyundeok {
namespace memory {
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
} // namespace memory
} // namespace hyundeok

#endif
