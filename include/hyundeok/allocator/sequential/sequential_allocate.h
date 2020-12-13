#ifndef HYUNDEOK_ALLOCATOR_SEQUENTIAL_SEQUENTIAL_ALLOCATE_H
#define HYUNDEOK_ALLOCATOR_SEQUENTIAL_SEQUENTIAL_ALLOCATE_H

#include "hyundeok/allocator/allocator_types.h"

namespace hyundeok {
namespace allocator {
namespace sequential {

auto SequentialAllocate(SizeT size) -> void*;
auto SequentialFree(void* ptr) -> void;

} // namespace sequential
} // namespace allocator
} // namespace hyundeok

#endif
