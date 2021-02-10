#include "gtest/gtest.h"

#include "hyundeok/allocator/allocator_utils.h"
#include "hyundeok/allocator/linked_list/free_list.h"
#include "hyundeok/allocator/linked_list/first_fit_search.h"

#include <utility>

using namespace hyundeok::allocator;
using namespace hyundeok::allocator::linked_list;

using DefaultFreeList = FreeList<FirstFitSearch<FindMatchHeap>>;

namespace {

TEST(TestFreeListConstructor, DefaultConstruction) {
  DefaultFreeList fl;
  EXPECT_EQ(fl.begin(), fl.end());
}

// TEST(TestDefaultFreeListConstructor, CopyConstructor) {
//   DefaultFreeList fl1;
//   EXPECT_DEATH(DefaultFreeList{fl1}, "");
// }

TEST(TestDefaultFreeListConstructor, MoveConstructor) {
  DefaultFreeList fl1;
  auto* node = RequestHeap(10);
  fl1.InsertFront(node);

  DefaultFreeList fl2{std::move(fl1)};

  EXPECT_EQ(fl1.begin(), fl1.end());
  EXPECT_NE(fl2.begin(), fl2.end());
  EXPECT_EQ(fl2.begin().node_, node);
}

TEST(TestDefaultFreeListInsertAfter, InsertAfter) {
  DefaultFreeList fl;
  auto* node = RequestHeap(10);

  fl.InsertAfter(fl.CBeforeBegin(), node);

  auto beg = fl.begin();

  EXPECT_EQ(beg->size_, 10);
  EXPECT_EQ(beg->used_, false);
  EXPECT_EQ(beg->next_, nullptr);

  EXPECT_EQ(++beg, fl.end());
}

TEST(TestDefaultFreeListInsertAfter, InsertAfterMultiple) {
  DefaultFreeList fl;

  auto bbeg = fl.CBeforeBegin();
  EXPECT_EQ(fl.begin(), fl.end());

  auto* heap1 = RequestHeap(64);
  auto* heap2 = RequestHeap(128);
  auto* heap3 = RequestHeap(256);

  fl.InsertAfter(bbeg, heap1);

  EXPECT_NE(fl.begin(), fl.end());
  EXPECT_EQ(bbeg->next_->size_, 64);
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_EQ(bbeg->next_->next_, nullptr);

  fl.InsertAfter(bbeg, heap2);

  EXPECT_NE(fl.begin(), fl.end());
  EXPECT_EQ(bbeg->next_->size_, 128);
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_NE(bbeg->next_->next_, nullptr);

  fl.InsertAfter(bbeg, heap3);

  EXPECT_NE(fl.begin(), fl.end());
  EXPECT_EQ(bbeg->next_->size_, 256);
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_NE(bbeg->next_->next_, nullptr);
}

TEST(TestDefaultFreeListInsertFront, Coalesce) {
  DefaultFreeList fl;

  auto bbeg = fl.CBeforeBegin();

  auto heap1 = RequestHeap(64);
  auto heap2 = RequestHeap(128);
  auto heap3 = RequestHeap(256);

  fl.InsertFront(heap1);

  EXPECT_EQ(bbeg->next_->size_, 64);
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_EQ(bbeg->next_->next_, nullptr);

  fl.InsertFront(heap2);

  EXPECT_EQ(bbeg->next_, heap1);
  EXPECT_EQ(bbeg->next_->size_, 128 + AllocateSize(64));
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_EQ(bbeg->next_->next_, nullptr);

  fl.InsertFront(heap3);

  EXPECT_NE(fl.begin(), fl.end());
  EXPECT_EQ(bbeg->next_->size_, 256 + AllocateSize(128 + AllocateSize(64)));
  EXPECT_EQ(bbeg->next_->used_, false);
  EXPECT_EQ(bbeg->next_->next_, nullptr);
}

TEST(TestDefaultFreeListReleaseNode, ReleaseNode) {
  DefaultFreeList fl;

  auto bbeg = fl.CBeforeBegin();

  fl.InsertAfter(bbeg, RequestHeap(64));
  fl.InsertAfter(bbeg, RequestHeap(128));
  fl.InsertAfter(bbeg, RequestHeap(256));

  auto beg = fl.begin();
  auto released1 = fl.ReleaseNode(120);

  EXPECT_EQ(released1->size_, 120);
  EXPECT_EQ(released1->used_, false);

  EXPECT_EQ(beg->size_, 256 - AllocateSize(120));
}

} // namespace
