#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/allocator_types.h"

#include "gtest/gtest.h"

#include <unistd.h>

#include <limits>

using hyundeok::allocator::AlignHeap;
// using hyundeok::allocator::GetHeapHeader;
using hyundeok::allocator::GetHeapStart;
using hyundeok::allocator::GetHeapTop;
using hyundeok::allocator::HeapHeader;
using hyundeok::allocator::kMaxPtrAddress;
using hyundeok::allocator::RequestHeap;
using hyundeok::allocator::SizeT;
using hyundeok::allocator::WordT;

namespace {

auto ComputeSize(SizeT size) -> SizeT {
  SizeT computed = size / sizeof(WordT) * 8;
  return size % sizeof(WordT) == 0 ? computed : computed + sizeof(WordT);
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

TEST(TestGetHeapStart, CorrectHeapStart) {
  EXPECT_EQ(sbrk(0), GetHeapStart());
  ASSERT_NE(nullptr, GetHeapStart());
}

TEST(TestGetHeapTop, InitialHeapTop) {
  ASSERT_EQ(GetHeapTop(), static_cast<HeapHeader*>(GetHeapStart()));
}

TEST(TestRequestHeap, NegativeSize) {
  ASSERT_DEATH(RequestHeap(-1), "");
}

TEST(TestRequestHeap, ExceedingMax) {
  ASSERT_DEATH(RequestHeap(SizeT(kMaxPtrAddress) + 1), "");
}

} // namespace
