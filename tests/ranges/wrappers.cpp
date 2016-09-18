#include <gtest/gtest.h>
#include <vector>
#include <spcppl/ranges/wrappers.hpp>
#include <spcppl/ranges/Range.hpp>

TEST(WrappersTest, Reversed) {
	EXPECT_EQ(reversed(std::vector<int>{5, 7, 2, 3}), (std::vector<int>{3, 2, 7, 5}));
}

TEST(WrappersTest, Sorted) {
	EXPECT_EQ(sorted(std::vector<int>{5, 7, 2, 3}), (std::vector<int>{2, 3, 5, 7}));
}

TEST(WrapperTest, SortedWithComparator) {
	EXPECT_EQ(sorted(std::vector<int>{5, 7, 2, 3}, std::greater<int>()), (std::vector<int>{7, 5, 3, 2}));
}

TEST(WrapperTest, Unique) {
	std::vector<int> v = {5, 7, 7, 7, 3};
	unique(v);
	EXPECT_EQ(v, (std::vector<int>{5, 7, 3}));
}

TEST(WrapperTest, UniquePreservesNotAdjascentElements) {
	std::vector<int> v = {1, 2, 1};
	std::vector<int> original_v = v;
	unique(v);
	EXPECT_EQ(v, original_v);
}

TEST(WrapperTest, FindsMaxElement) {
	std::vector<int> v = {5, 7, 3};
	EXPECT_EQ(*max_element(v), 7);
}

TEST(WrapperTest, MaxOfEmptyRangeIsBegin) {
	std::vector<int> v;
	EXPECT_EQ(max_element(v), v.begin());
}

TEST(WrapperTest, FindsMinElement) {
	std::vector<int> v = {5, 7, 3};
	EXPECT_EQ(*min_element(v), 3);
}

TEST(WrapperTest, MinOfEmptyRangeIsBegin) {
	std::vector<int> v;
	EXPECT_EQ(min_element(v), v.begin());
}

TEST(WrapperTest, FindsMaxOfPartOfRange) {
	std::vector<int> v = {100, 1, 2, 5, 0, 15, -1};
	EXPECT_EQ(*max_element(make_range(v.begin() + 1, v.begin() + 4)), 5);
}

TEST(WrappersTest, FindsNextPermutation) {
	std::vector<int> v = {1, 3, 2};
	EXPECT_TRUE(next_permutation(v));
	EXPECT_EQ(v, (std::vector<int>{2, 1, 3}));
}

TEST(WrappersTest, NextPermuationCyclesAfterLastPermutation) {
	std::vector<int> v = {3, 2, 1};
	EXPECT_FALSE(next_permutation(v));
	EXPECT_EQ(v, (std::vector<int>{1, 2, 3}));
}
