#include <spcppl/dataStructures/TreapMultiset.hpp>
#include <gtest/gtest.h>

TEST(TreapMultisetTest, IndexingInSortedOrder) {
	TreapMultiset<int> tree;
	tree.insert(3);
	tree.insert(7);
	tree.insert(1);

	ASSERT_EQ(tree.size(), static_cast<std::size_t>(3));

	EXPECT_EQ(tree[0], 1);
	EXPECT_EQ(tree[1], 3);
	EXPECT_EQ(tree[2], 7);
}

TEST(TreapMultisetTest, HandlesSameArgumentsCorrectly) {
	TreapMultiset<int> tree;
	tree.insert(5);
	tree.insert(5);
	tree.insert(1);

	EXPECT_EQ(tree.size(), static_cast<std::size_t>(3));

	tree.erase_one(5);

	ASSERT_EQ(tree.size(), static_cast<std::size_t>(2));
	EXPECT_EQ(tree[0], 1);
	EXPECT_EQ(tree[1], 5);
}
