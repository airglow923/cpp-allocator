#ifndef HYUNDEOK_ALLOCATOR_ALLOCATOR_TYPES_H
#define HYUNDEOK_ALLOCATOR_ALLOCATOR_TYPES_H

#include <cstdint>

namespace hyundeok {
namespace allocator {

namespace {

using LL = signed long long int;

template <LL N, LL X>
struct PowerOf {
  static constexpr LL value_ = N * PowerOf<N, X - 1>::value_;
};

template <LL N>
struct PowerOf<N, 0> {
  static constexpr LL value_ = 1;
};

template <LL N, LL X>
inline constexpr LL PowerOfV = PowerOf<N, X>::value_;

} // namespace

using WordT = std::intptr_t;
using SizeT = std::size_t;

static inline constexpr auto kMaxPtrAddress = PowerOfV<2, sizeof(WordT)> - 1;

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
