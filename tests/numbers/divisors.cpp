#include <gtest/gtest.h>
#include <spcppl/numbers/divisors.hpp>

TEST(DivisorsTest, DivisorsTest) {
	EXPECT_EQ(sortedDivisors(24), (std::vector<int>{1, 2, 3, 4, 6, 8, 12, 24}));
}

TEST(DivisorsTest, HandlesPower) {
	EXPECT_EQ(sortedDivisors(27), (std::vector<int>{1, 3, 9, 27}));
}

TEST(DivisorsTest, HandlesOnes) {
	EXPECT_EQ(sortedDivisors(1), (std::vector<int>{1}));
}
