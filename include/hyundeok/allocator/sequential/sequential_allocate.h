#ifndef HYUNDEOK_ALLOCATOR_SEQUENTIAL_SEQUENTIAL_ALLOCATE_H
#define HYUNDEOK_ALLOCATOR_SEQUENTIAL_SEQUENTIAL_ALLOCATE_H

#include "hyundeok/allocator/allocator_types.h"
#include "hyundeok/allocator/allocator_utils.h"

namespace hyundeok {
namespace allocator {
namespace sequential {

auto SequentialAllocate(SizeT size) -> void*;
auto SequentialFree(void* ptr) -> int;

} // namespace sequential
} // namespace allocator
} // namespace hyundeok

#endif
