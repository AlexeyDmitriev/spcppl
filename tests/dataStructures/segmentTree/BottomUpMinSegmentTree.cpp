#include <spcppl/dataStructures/segmentTree/BottomUpMinSegmentTree.hpp>
#include <gtest/gtest.h>
#include <vector>

TEST(BottomUpMinSegmentTree, CreationFromNumber) {
	BottomUpMinSegmentTree<int> tree(5);
	EXPECT_EQ(tree.getElement(3), PositiveInfinity<int>()());
}

TEST(BottomUpMinSegmentTree, CreationFromList) {
	BottomUpMinSegmentTree<int> tree(std::vector<int>{1, 3, 2, 5, 4});
	EXPECT_EQ(tree.getResult(1, 3), 2);
	EXPECT_EQ(tree.getResult(0, 5), 1);
	EXPECT_EQ(tree.getElement(0), 1);
}

TEST(BottomUpMinSegmentTree, FindFirstMinimum) {
	BottomUpMinSegmentTree<int> tree(std::vector<int>{3, 2, 3, 4, 2});
	EXPECT_EQ(tree.getResult(0, 5), 2);
	EXPECT_EQ(tree.getFirstMinimum(), 1u);

	tree.set(1, 5);
	EXPECT_EQ(tree.getFirstMinimum(), 4u);

	tree.set(2, 1);
	EXPECT_EQ(tree.getFirstMinimum(), 2u);
}
