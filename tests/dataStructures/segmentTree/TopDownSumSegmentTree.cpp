// Confidential Information. "AIM High Tech" LLC

#include <gtest/gtest.h>
#include <spcppl/dataStructures/segmentTree/TopDownSumSegmentTree.hpp>

TEST(TopDownSumSegmentTree, CreationFromNumber) {
	TopDownSumSegmentTree<int> tree(5);
	EXPECT_EQ(tree.getResult(3, 4), 0);
}

TEST(TopDownSumSegmentTree, CreationFromList) {
	TopDownSumSegmentTree<int> tree(std::vector<int>{1, 3, 2, 5, 4});
	EXPECT_EQ(tree.getResult(1, 3), 5);
	EXPECT_EQ(tree.getResult(0, 5), 15);
}

TEST(TopDownSumSegmentTree, GetFirstPrefixAtLeast) {
	TopDownSumSegmentTree<int> tree(std::vector<int>{1, 3, 2, 5, 4});
	tree.getFirstPrefixAtLeast(0);
	EXPECT_EQ(tree.getFirstPrefixAtLeast(0), 0u);
	EXPECT_EQ(tree.getFirstPrefixAtLeast(3), 2u);
	EXPECT_EQ(tree.getFirstPrefixAtLeast(25), 6u);
	EXPECT_EQ(tree.getFirstPrefixAtLeast(6), 3u);
	EXPECT_EQ(tree.getFirstPrefixAtLeast(5), 3u);
}

