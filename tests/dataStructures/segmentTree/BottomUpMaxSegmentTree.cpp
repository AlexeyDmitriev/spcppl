#include <spcppl/dataStructures/segmentTree/BottomUpMaxSegmentTree.hpp>
#include <gtest/gtest.h>
#include <vector>

TEST(BottomUpMaxSegmentTree, CreationFromNumber) {
	BottomUpMaxSegmentTree<int> tree(5);
	EXPECT_EQ(tree.getElement(3), NegativeInfinity<int>()());
}

TEST(BottomUpMaxSegmentTree, CreationFromList) {
	BottomUpMaxSegmentTree<int> tree(std::vector<int>{1, 3, 2, 5, 4});
	EXPECT_EQ(tree.getResult(1, 3), 3);
	EXPECT_EQ(tree.getResult(0, 5), 5);
	EXPECT_EQ(tree.getElement(0), 1);
}

TEST(BottomUpMaxSegmentTree, FindFirstMinimum) {
	BottomUpMaxSegmentTree<int> tree(std::vector<int>{3, 2, 3, 8, 2});
	EXPECT_EQ(tree.getResult(0, 5), 8);
	EXPECT_EQ(tree.getFirstMaximum(), 3u);

	tree.set(2, 8);
	EXPECT_EQ(tree.getFirstMaximum(), 2u);

	tree.set(4, 10);
	EXPECT_EQ(tree.getFirstMaximum(), 4u);
}
