#ifndef HYUNDEOK_ALLOCATOR_SEQUENTIAL_SEQUENTIAL_ALLOCATE_HPP_
#define HYUNDEOK_ALLOCATOR_SEQUENTIAL_SEQUENTIAL_ALLOCATE_HPP_

#include "hyundeok/allocator/allocator_types.hpp"

namespace hyundeok {
namespace allocator {
namespace sequential {

auto sequential_allocate(size_t size) -> void*;
auto sequential_free(void* ptr) -> void;

} // namespace sequential
} // namespace allocator
} // namespace hyundeok

#endif
