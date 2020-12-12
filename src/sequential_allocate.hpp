#pragma once

#ifndef __HYUNDEOK_MEMORY_ALLOCATOR_SEQUENTIAL_ALLOCATE_HPP__
#define __HYUNDEOK_MEMORY_ALLOCATOR_SEQUENTIAL_ALLOCATE_HPP__

#include "memory_types.hpp"

namespace hyundeok {
namespace memory {
namespace allocator {

auto sequential_allocate(size_t size) -> void*;
auto sequential_free(void* ptr) -> void;

} // namespace allocator
} // namespace memory
} // namespace hyundeok

#endif
