#include "sequential_allocate.hpp"

#include <unistd.h>

#include <utility>

namespace hyundeok {
namespace memory {
namespace allocator {

namespace {

HeapHeader* heap_start = nullptr;
HeapHeader* top = nullptr;

auto align_heap(size_t n) -> word_t {
  return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}

/*
 * Why not sizeof(word_t)?
 *
 * Because the size of a variable is not guaranteed to be the same as the size
 * of an array with length 1.
 */
auto allocate_size(size_t size) -> size_t {
  return size + sizeof(HeapHeader) - sizeof(std::declval<HeapHeader>().data_);
}

auto request_heap(size_t size) -> HeapHeader* {
  auto heap = static_cast<HeapHeader*>(sbrk(0));

  if (sbrk(allocate_size(size)) == (void*)-1)
    heap = nullptr;

  return heap;
}

auto get_heap_header(void* heap) -> HeapHeader* {
  return (HeapHeader*)heap - sizeof(HeapHeader) +
         sizeof(std::declval<HeapHeader>().data_);
}

} // namespace

auto sequential_allocate(size_t size) -> void* {
  size = align_heap(size);

  auto heap = request_heap(size);
  heap->size_ = size;
  heap->used_ = true;

  if (heap_start == nullptr)
    heap_start = heap;

  if (top != nullptr)
    top->next_ = heap;

  top = heap;

  return heap->data_;
}

auto sequential_free(void* ptr) -> void {
  auto heap_header = get_heap_header(ptr);
  heap_header->used_ = false;
}

} // namespace allocator
} // namespace memory
} // namespace hyundeok
