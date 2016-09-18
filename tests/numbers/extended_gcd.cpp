#include <gtest/gtest.h>
#include <spcppl/numbers/extendedGcd.hpp>

TEST(ExtendedGcdTest, HandlesCoPrimes) {
	int x, y;
	EXPECT_EQ(extendedGcd(3, 5, x, y), 1);
	EXPECT_EQ(x * 3 + y * 5, 1);

	EXPECT_EQ(extendedGcd(8, 9, x, y), 1);
	EXPECT_EQ(x * 8 + y * 9, 1);
}

TEST(ExtendedGcdTest, HandlesDivisible) {
	int x, y;
	EXPECT_EQ(extendedGcd(2, 8, x, y), 2);
	EXPECT_EQ(x * 2 + y * 8, 2);

	EXPECT_EQ(extendedGcd(9, 3, x, y), 3);
	EXPECT_EQ(x * 9 + y * 3, 3);
}

TEST(ExtendedGcdTest, HandlesZero) {
	int x, y;
	EXPECT_EQ(extendedGcd(0, 5, x, y), 5);
	EXPECT_EQ(y, 1);

	EXPECT_EQ(extendedGcd(7, 0, x, y), 7);
	EXPECT_EQ(x, 1);
}

TEST(ExtendedGcdTest, HandlesNOnTrivialGcd) {
	int x, y;
	EXPECT_EQ(extendedGcd(15, 40, x, y), 5);
	EXPECT_EQ(x * 15 + y * 40, 5);
}

TEST(ExtendedGcdTest, HandlesNegatives) {
	int x, y;
	int g = extendedGcd(-2, 5, x, y);
	EXPECT_EQ(abs(g), 1);
	EXPECT_EQ(x * (-2) + y * 5, g);
}
