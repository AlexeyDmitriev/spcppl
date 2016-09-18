#include <gtest/gtest.h>
#include <spcppl/numbers/bits.hpp>

TEST(IsPowerOf2Test, DetectPowersOf2) {
	EXPECT_TRUE(isPowerOf2(1));
	EXPECT_TRUE(isPowerOf2(32));
	EXPECT_TRUE(isPowerOf2(1 << 30));
	EXPECT_TRUE(isPowerOf2(4));
}

TEST(IsPowerOf2Test, DoesntDetectNotPowers) {
	EXPECT_FALSE(isPowerOf2(3));
	EXPECT_FALSE(isPowerOf2(0));
	EXPECT_FALSE(isPowerOf2(42));
	EXPECT_FALSE(isPowerOf2((1 << 15) - 1));
}

TEST(LeastSignificantBitTest, LeastSignificantBit) {
	EXPECT_EQ(leastSignificantBit(15), static_cast<std::size_t>(0));
	EXPECT_EQ(leastSignificantBit(1 << 30), static_cast<std::size_t>(30));
	EXPECT_EQ(leastSignificantBit(36), static_cast<std::size_t>(2));
}
