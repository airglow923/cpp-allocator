#include "hyundeok/allocator/allocator_commons.h"
#include "hyundeok/allocator/allocator_types.h"

#include "gtest/gtest.h"

#include <unistd.h>

using hyundeok::allocator::AlignHeap;
// using hyundeok::allocator::GetHeapHeader;
using hyundeok::allocator::GetHeapStart;
using hyundeok::allocator::GetHeapTop;
using hyundeok::allocator::HeapHeader;
// using hyundeok::allocator::RequestHeap;
using hyundeok::allocator::SizeT;
using hyundeok::allocator::WordT;

namespace {

TEST(TestAlignHeap, AlignSize) {
  EXPECT_EQ(AlignHeap(1), sizeof(WordT));
  EXPECT_EQ(AlignHeap(2), sizeof(WordT));
  EXPECT_EQ(AlignHeap(3), sizeof(WordT));
  EXPECT_EQ(AlignHeap(4), sizeof(WordT));
  EXPECT_EQ(AlignHeap(5), sizeof(WordT));
  EXPECT_EQ(AlignHeap(6), sizeof(WordT));
  EXPECT_EQ(AlignHeap(7), sizeof(WordT));
  EXPECT_EQ(AlignHeap(8), sizeof(WordT));
  EXPECT_EQ(AlignHeap(10), sizeof(WordT) * 2);
  EXPECT_EQ(AlignHeap(16), sizeof(WordT) * 2);
  EXPECT_EQ(AlignHeap(56), sizeof(WordT) * 7);
  EXPECT_EQ(AlignHeap(60), sizeof(WordT) * 8);
  EXPECT_EQ(AlignHeap(64), sizeof(WordT) * 8);
}

TEST(TestAlignHeap, NegativeAlignSize) {
  EXPECT_EQ(AlignHeap(-1), 0);
  EXPECT_EQ(AlignHeap(-128), static_cast<SizeT>(-1) - 127);
  EXPECT_EQ(AlignHeap(-256), static_cast<SizeT>(-1) - 255);
}

TEST(TestGetHeapHeader, GetHeapHeader) {}

TEST(TestGetHeapStart, CorrectHeapStart) {
  EXPECT_EQ(sbrk(0), GetHeapStart());
  ASSERT_NE(nullptr, GetHeapStart());
}

TEST(TestGetHeapTop, InitialHeapTop) {
  ASSERT_EQ(GetHeapTop(), static_cast<HeapHeader*>(GetHeapStart()));
}

TEST(TestRequestHeap, Placeholder) {}

} // namespace
