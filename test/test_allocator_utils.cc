#include "gtest/gtest.h"

#include "hyundeok/allocator/allocator_utils.h"

#include <unistd.h>

#include <utility>     // declval
#include <type_traits> // is_same

using namespace hyundeok::allocator;

namespace {

constexpr auto kWordSize = sizeof(SizeT);

auto ComputeSize(SizeT size) -> SizeT {
  SizeT computed = size / sizeof(WordT) * 8;
  return size % sizeof(WordT) == 0 ? computed : computed + sizeof(WordT);
}

TEST(TestComputeDataAlignment, AlignmentOnDiffArch) {
  switch (kWordSize) {
  case 4:
    EXPECT_EQ(ComputeDataAlignment(), 3);
  case 8:
    EXPECT_EQ(ComputeDataAlignment(), 7);
  }
}

TEST(TestGetHeapStart, EqualToHeapStart) {
  auto* head = sbrk(0);

  ASSERT_NE(head, reinterpret_cast<void*>(-1));
  EXPECT_EQ(GetHeapStart(), head);
}

TEST(TestGetHeapEnd, HeapEndNextFreeBlock) {
  auto* heap1 = RequestHeap(10);
  auto* heap2 = RequestHeap(30);
  ASSERT_EQ(GetHeapEnd(GetHeapEnd(heap1)), GetHeapEnd(heap2));
}

TEST(TestAllocateSize, CorrectSize) {
  const SizeT i = 32;
  EXPECT_EQ(AllocateSize(i), i + sizeof(HeapHeader) - ComputeDataAlignment());
}

TEST(TestAlignHeap, AlignSize) {
  EXPECT_EQ(AlignHeap((1)), ComputeSize((1)));
  EXPECT_EQ(AlignHeap((2)), ComputeSize((2)));
  EXPECT_EQ(AlignHeap((3)), ComputeSize((3)));
  EXPECT_EQ(AlignHeap((4)), ComputeSize((4)));
  EXPECT_EQ(AlignHeap((5)), ComputeSize((5)));
  EXPECT_EQ(AlignHeap((6)), ComputeSize((6)));
  EXPECT_EQ(AlignHeap((7)), ComputeSize((7)));
  EXPECT_EQ(AlignHeap((8)), ComputeSize((8)));
  EXPECT_EQ(AlignHeap((10)), ComputeSize((10)));
  EXPECT_EQ(AlignHeap((16)), ComputeSize((16)));
  EXPECT_EQ(AlignHeap((56)), ComputeSize((56)));
  EXPECT_EQ(AlignHeap((60)), ComputeSize((60)));
  EXPECT_EQ(AlignHeap((64)), ComputeSize((64)));
}

TEST(TestAlignHeap, NegativeAlignSize) {
  EXPECT_EQ(AlignHeap(-1), 0);
  EXPECT_EQ(AlignHeap(-128), static_cast<SizeT>(-1) - 127);
  EXPECT_EQ(AlignHeap(-256), static_cast<SizeT>(-1) - 255);
}

TEST(TestConvertPtrToCharPtr, TestAnyPtr) {
  // since macros prioritize a delimiter (comma) over expression, wrap argument
  // with parentheses
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToCharPtr(std::declval<short*>())),
                      char*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToCharPtr(std::declval<int*>())),
                      char*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToCharPtr(std::declval<long*>())),
                      char*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToCharPtr(std::declval<long long*>())),
                      char*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToCharPtr(std::declval<float*>())),
                      char*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToCharPtr(std::declval<double*>())),
                      char*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToCharPtr(std::declval<double*>())),
                      char*>));
}

TEST(TestConvertPtrToHeapHeader, TestAnyPtr) {
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToHeapHeader(std::declval<short*>())),
                      HeapHeader*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToHeapHeader(std::declval<int*>())),
                      HeapHeader*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToHeapHeader(std::declval<long*>())),
                      HeapHeader*>));
  EXPECT_TRUE((std::is_same_v<decltype(ConvertPtrToHeapHeader(
                                  std::declval<long long*>())),
                              HeapHeader*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToHeapHeader(std::declval<float*>())),
                      HeapHeader*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToHeapHeader(std::declval<double*>())),
                      HeapHeader*>));
  EXPECT_TRUE(
      (std::is_same_v<decltype(ConvertPtrToHeapHeader(std::declval<double*>())),
                      HeapHeader*>));
}

// TEST(TestRequestHeap, NegativeSize) { ASSERT_DEATH(RequestHeap(-1), ""); }

// TEST(TestRequestHeap, ExceedingMax) {
//   ASSERT_DEATH(RequestHeap(SizeT(kMaxPtrAddress) + 1), "");
// }

TEST(TestGetHeapHeader, GetHeapHeader) {
  auto* heap = RequestHeap(10);
  auto* header = GetHeapHeader(heap->data_);
  EXPECT_EQ(heap, header);
}

TEST(TestInitializeHeapHeader, InitializeHeap) {
  const int size = 10;
  auto* heap = RequestHeap(size);
  InitializeHeapHeader(heap, size);

  EXPECT_EQ(heap->size_, size);
  EXPECT_EQ(heap->used_, false);
  EXPECT_EQ(heap->next_, nullptr);
}

} // namespace
