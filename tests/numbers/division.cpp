#include <gtest/gtest.h>
#include <spcppl/numbers/division.hpp>

TEST(DivideCeilTest, PositiveWholeDivision) {
	EXPECT_EQ(divideCeil(6, 2), 3);
	EXPECT_EQ(divideCeil(48, 12), 4);
}

TEST(DivideCeilTest, PositiveNotWholeDivision) {
	EXPECT_EQ(divideCeil(17, 2), 9);
	EXPECT_EQ(divideCeil(101, 5), 21);
	EXPECT_EQ(divideCeil(1, 101), 1);
}

TEST(DivideCeilTest, NegativeWholeDivions) {
	EXPECT_EQ(divideCeil(-70, -5), 14);
	EXPECT_EQ(divideCeil(12, -4), -3);
	EXPECT_EQ(divideCeil(-8, 2), -4);
}

TEST(DivideCeilTest, NegativesNotWholeDivision) {
	EXPECT_EQ(divideCeil(-33, 5), -6);
	EXPECT_EQ(divideCeil(23, -3), -7);
	EXPECT_EQ(divideCeil(-15, -2), 8);
	EXPECT_EQ(divideCeil(-1, 5), 0);
}

TEST(DivideFloorTest, PositiveWholeDivision) {
	EXPECT_EQ(divideFloor(6, 2), 3);
	EXPECT_EQ(divideFloor(48, 12), 4);
}

TEST(DivideFloorTest, PositiveNotWholeDivision) {
	EXPECT_EQ(divideFloor(17, 2), 8);
	EXPECT_EQ(divideFloor(101, 5), 20);
	EXPECT_EQ(divideFloor(1, 101), 0);
}

TEST(DivideFloorTest, NegativeWholeDivions) {
	EXPECT_EQ(divideFloor(-70, -5), 14);
	EXPECT_EQ(divideFloor(12, -4), -3);
	EXPECT_EQ(divideFloor(-8, 2), -4);
}

TEST(DivideFloorTest, NegativesNotWholeDivision) {
	EXPECT_EQ(divideFloor(-33, 5), -7);
	EXPECT_EQ(divideFloor(23, -3), -8);
	EXPECT_EQ(divideFloor(-15, -2), 7);
	EXPECT_EQ(divideFloor(-1, 5), -1);
}

TEST(DivideTowardsZeroTest, PositiveWholeDivision) {
	EXPECT_EQ(divideTowardsZero(6, 2), 3);
	EXPECT_EQ(divideTowardsZero(48, 12), 4);
}

TEST(DivideTowardsZeroTest, PositiveNotWholeDivision) {
	EXPECT_EQ(divideTowardsZero(17, 2), 8);
	EXPECT_EQ(divideTowardsZero(101, 5), 20);
	EXPECT_EQ(divideTowardsZero(1, 101), 0);
}

TEST(DivideTowardsZeroTest, NegativeWholeDivions) {
	EXPECT_EQ(divideTowardsZero(-70, -5), 14);
	EXPECT_EQ(divideTowardsZero(12, -4), -3);
	EXPECT_EQ(divideTowardsZero(-8, 2), -4);
}

TEST(DivideTowardsZeroTest, NegativesNotWholeDivision) {
	EXPECT_EQ(divideTowardsZero(-33, 5), -6);
	EXPECT_EQ(divideTowardsZero(23, -3), -7);
	EXPECT_EQ(divideTowardsZero(-15, -2), 7);
	EXPECT_EQ(divideTowardsZero(-1, 5), 0);
}

TEST(DivideAwayFromZeroTest, PositiveWholeDivision) {
	EXPECT_EQ(divideAwayFromZero(6, 2), 3);
	EXPECT_EQ(divideAwayFromZero(48, 12), 4);
}

TEST(DivideAwayFromZeroTest, PositiveNotWholeDivision) {
	EXPECT_EQ(divideAwayFromZero(17, 2), 9);
	EXPECT_EQ(divideAwayFromZero(101, 5), 21);
	EXPECT_EQ(divideAwayFromZero(1, 101), 1);
}

TEST(DivideAwayFromZeroTest, NegativeWholeDivions) {
	EXPECT_EQ(divideAwayFromZero(-70, -5), 14);
	EXPECT_EQ(divideAwayFromZero(12, -4), -3);
	EXPECT_EQ(divideAwayFromZero(-8, 2), -4);
}

TEST(DivideAwayFromZeroTest, NegativesNotWholeDivision) {
	EXPECT_EQ(divideAwayFromZero(-33, 5), -7);
	EXPECT_EQ(divideAwayFromZero(23, -3), -8);
	EXPECT_EQ(divideAwayFromZero(-15, -2), 8);
	EXPECT_EQ(divideAwayFromZero(-1, 5), -1);
}
