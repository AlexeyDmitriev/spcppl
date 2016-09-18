#include <gtest/gtest.h>
#include <spcppl/numbers/lcm.hpp>

TEST(LcmTest, CalculatesLcm) {
	EXPECT_EQ(lcm(3, 5), 15);
	EXPECT_EQ(lcm(2, 8), 8);
	EXPECT_EQ(lcm(6, 8), 24);
	EXPECT_EQ(lcm(10, 1), 10);
}
