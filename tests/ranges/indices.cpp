#include <spcppl/ranges/indices.hpp>
#include <gtest/gtest.h>

TEST(IndicesTest, ReturnFirstIndices) {
	EXPECT_EQ(indices(3), (std::vector<int>{0, 1, 2}));
}

TEST(IndicesTest, WorksWithEmptyRange) {
	EXPECT_EQ(indices(0), std::vector<int>());
}

TEST(IndicesTest, DetectsTypes) {
	int64_t x = 5;
	static_assert(std::is_same<decltype(indices(x)), std::vector<int64_t>>::value);
	static_assert(std::is_same<decltype(indices(5)), std::vector<int>>::value);
}
