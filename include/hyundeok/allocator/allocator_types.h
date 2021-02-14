#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_TYPES_H
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_TYPES_H

#include <cstdint>
#include <limits>

namespace hyundeok::allocator {

using WordT = std::uintptr_t;
using SizeT = std::size_t;

inline constexpr auto kMaxPtrAddress = std::numeric_limits<long>::max();

/*
 * next_ points to the first address of the next heap block.
 * data_ ponits to the first byte of the actual data.
 *
 * The data members are ordered by size in ascending order in an attemp to
 * reduce the size of the structure.
 */
struct HeapHeader {
  SizeT size_;
  HeapHeader* next_;
  bool used_;
  char data_[1];
};

} // namespace hyundeok::allocator

#endif
