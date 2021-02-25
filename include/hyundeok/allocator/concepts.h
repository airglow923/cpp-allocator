#ifndef HYUNDEOK_ALLOCATOR_CONCEPTS_H
#define HYUNDEOK_ALLOCATOR_CONCEPTS_H

#include "hyundeok/allocator/types.h"

#include <type_traits>

namespace hyundeok::allocator {

template <typename Fn>
concept HeapComparePolicy = std::is_invocable_r_v<bool, Fn, HeapHeader*, SizeT>;

template <typename Fn>
concept HeapSearchPolicy =
    std::is_invocable_r_v<HeapHeader*, Fn, HeapHeader*, SizeT>;

} // namespace hyundeok::allocator

#endif
