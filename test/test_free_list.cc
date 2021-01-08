#include "gtest/gtest.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list.h"

using namespace hyundeok::allocator;
using namespace hyundeok::allocator::linked_list;

namespace {

TEST(TestGetHeapStart, EqualToHeapStart) {
  auto* head = sbrk(0);

  ASSERT_NE(head, reinterpret_cast<void*>(-1));
  EXPECT_EQ(GetHeapStart(), head);
}

TEST(TestGetHeapStartHeader, HeapStartSentinel) {
  EXPECT_EQ(GetHeapStartHeader(), GetSentinelNode());
}

TEST(TestGetHeapEnd, HeapEndNextFreeBlock) {
  auto* heap1 = RequestHeap(10);
  auto* heap2 = RequestHeap(30);
  ASSERT_EQ(GetHeapEnd(GetHeapEnd(heap1)), GetHeapEnd(heap2));
}

TEST(TestAllocateSize, CorrectSize) {
  const SizeT i = 32;
  EXPECT_EQ(AllocateSize(i),
            i + sizeof(HeapHeader) - ComputeDataAlignment());
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

TEST(TestFindMatchHeap, FindMatchHeap) {
  auto* heap1 = RequestHeap(10);
  auto* heap2 = RequestHeap(16);

  heap2->used_ = true;

  EXPECT_TRUE(FindMatchHeap(heap1, 9));
  EXPECT_TRUE(FindMatchHeap(heap1, 10));
  EXPECT_FALSE(FindMatchHeap(heap1, 11));

  EXPECT_FALSE(FindMatchHeap(heap2, 15));
  EXPECT_FALSE(FindMatchHeap(heap2, 16));
  EXPECT_FALSE(FindMatchHeap(heap2, 17));
}

TEST(TestInitializeHeapHeader, InitializeHeap) {
  const int size = 10;
  auto* heap = RequestHeap(size);
  InitializeHeapHeader(heap, size);

  EXPECT_EQ(heap->size_, size);
  EXPECT_EQ(heap->used_, false);
  EXPECT_EQ(heap->next_, GetSentinelNode());
}

TEST(TestSplitHeap, SplitHeap) {
  const SizeT size = 64;
  auto* heap1 = RequestHeap(size);
  auto* split1 = SplitHeap(heap1, 10);

  EXPECT_NE(split1, nullptr);
  EXPECT_EQ(heap1->size_, size - AllocateSize(10));
  EXPECT_EQ(split1->size_, 10);
  EXPECT_EQ(GetHeapEnd(heap1), split1);
}

}
