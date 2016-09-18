#include <gtest/gtest.h>
#include <spcppl/numbers/gcd.hpp>

TEST(GcdTest, HandlesPositiveNumbers) {
	EXPECT_EQ(gcd(5, 7), 1);
	EXPECT_EQ(gcd(20, 20), 20);
	EXPECT_EQ(gcd(4, 6), 2);
	EXPECT_EQ(gcd(1, 19), 1);
	EXPECT_EQ(gcd(3, 21), 3);
	EXPECT_EQ(gcd(14, 2), 2);
}

TEST(GcdTest, GcdOfZeroIsOtherNumber) {
	EXPECT_EQ(gcd(0, 0), 0);
	EXPECT_EQ(gcd(0, 3), 3);
	EXPECT_EQ(gcd(60, 0), 60);
}

TEST(GcdTest, HandlesNegatives) {
	EXPECT_EQ(abs(gcd(-2, 6)), 2);
	EXPECT_EQ(abs(gcd(-15, -40)), 5);
	EXPECT_EQ(abs(gcd(5, -7)), 1);
}
