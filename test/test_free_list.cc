#include "gtest/gtest.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list.h"

#include <utility>

using namespace hyundeok::allocator;
using namespace hyundeok::allocator::linked_list;

namespace {

TEST(TestClearFreeList, ClearFreeList) { ClearFreeList(); }

TEST(TestInsertFront, InsertFront) {
  auto* heap = RequestHeap(10);
  auto* node = InsertFront(heap);

  EXPECT_EQ(node->size_, 10);
  EXPECT_EQ(node->used_, false);
  EXPECT_NE(node->next_, nullptr);

  ClearFreeList();
}

TEST(TestInsertFront, InsertFrontMultipleAndCoalesce) {
  auto* bbeg = GetFreeListBeforeBegin();
  auto* heap1 = RequestHeap(64);
  auto* heap2 = RequestHeap(128);
  auto* heap3 = RequestHeap(256);

  InsertFront(heap1);

  EXPECT_EQ(bbeg->next_->size_, 64);
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_EQ(bbeg->next_->next_, GetFreeListBeforeBegin());

  InsertFront(heap2);

  EXPECT_EQ(bbeg->next_->size_, 128 + AllocateSize(64));
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_EQ(bbeg->next_->next_, GetFreeListBeforeBegin());

  InsertFront(heap3);

  EXPECT_EQ(bbeg->next_->size_, 256 + AllocateSize(128 + AllocateSize(64)));
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_EQ(bbeg->next_->next_, GetFreeListBeforeBegin());

  ClearFreeList();
}

TEST(TestReleaseNode, ReleaseNode) {
  InsertFront(RequestHeap(64));
  InsertFront(RequestHeap(128));
  InsertFront(RequestHeap(256));

  auto* released = ReleaseNode(120);

  EXPECT_EQ(released->size_, 120);
  EXPECT_EQ(released->used_, false);

  ClearFreeList();
}

} // namespace
