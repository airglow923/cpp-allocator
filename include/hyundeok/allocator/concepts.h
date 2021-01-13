#ifndef HYUNDEOK_ALLOCATOR_CONCEPTS_H
#define HYUNDEOK_ALLOCATOR_CONCEPTS_H

#include "hyundeok/allocator/allocator_types.h"

#include <type_traits>

namespace hyundeok::allocator {

template <typename Fn>
concept HeapComparePolicy = std::is_invocable_r_v<bool, Fn, HeapHeader*, SizeT>;

template <typename Fn, typename Compare>
concept HeapSearchPolicy =
    std::is_invocable_r_v<HeapHeader*, Fn, HeapHeader*, SizeT, Compare>;

} // namespace hyundeok::allocator

#endif
