#ifndef _HYUNDEOK_ALLOCATOR_CONCEPTS_H_
#define _HYUNDEOK_ALLOCATOR_CONCEPTS_H_

#include "hyundeok/allocator/allocator_types.h"

#include <type_traits>

namespace hyundeok::allocator {

template <typename Fn>
concept HeapComparePolicy = std::is_invocable_r_v<bool, Fn, HeapHeader*, SizeT>;

template <typename Fn, typename Compare>
concept HeapSearchPolicy =
    std::is_invocable_r_v<HeapHeader*, Fn, SizeT, Compare>;

} // namespace hyundeok::allocator

#endif
