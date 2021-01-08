#include "gtest/gtest.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list.h"

using namespace hyundeok::allocator;
using namespace hyundeok::allocator::linked_list;

namespace {

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
