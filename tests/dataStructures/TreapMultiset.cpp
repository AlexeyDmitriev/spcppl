#include <spcppl/dataStructures/TreapMultiset.hpp>
#include <gtest/gtest.h>

TEST(TreapMultisetTest, IndexingInSortedOrder) {
	TreapMultiset<int> set;
	set.insert(3);
	set.insert(7);
	set.insert(1);

	ASSERT_EQ(set.size(), static_cast<std::size_t>(3));

	EXPECT_EQ(set[0], 1);
	EXPECT_EQ(set[1], 3);
	EXPECT_EQ(set[2], 7);
}

TEST(TreapMultisetTest, HandlesSameArgumentsCorrectly) {
	TreapMultiset<int> set;
	set.insert(5);
	set.insert(5);
	set.insert(1);

	EXPECT_EQ(set.size(), static_cast<std::size_t>(3));

	set.erase_one(5);

	ASSERT_EQ(set.size(), static_cast<std::size_t>(2));
	EXPECT_EQ(set[0], 1);
	EXPECT_EQ(set[1], 5);
}

TEST(TreapMultisetTest, HandlesMoveOnlyType) {
	TreapMultiset<std::unique_ptr<int>> set;
	set.insert(std::make_unique<int>(5));
	EXPECT_EQ(*set[0], 5);
}

TEST(TreapMultisetTest, HandlesImmovableType) {
	TreapMultiset<std::atomic<int>> set;
	set.emplace();
}
