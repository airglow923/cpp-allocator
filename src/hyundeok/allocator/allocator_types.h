#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_TYPES_H
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_TYPES_H

#include <cstdint>

namespace hyundeok {
namespace allocator {

using WordT = std::intptr_t;
using SizeT = std::size_t;

/*
 * next_ points to the first address of the next heap block.
 * data_ ponits to the first byte of the actual data.
 */
struct HeapHeader {
  SizeT size_;
  bool used_;
  HeapHeader* next_;
  char data_[1];
};

} // namespace allocator
} // namespace hyundeok

#endif
