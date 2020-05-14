#include <gtest/gtest.h>
#include <spcppl/geometry/Point2D.hpp>

TEST(Point2D, TriangleAreaTest) {
	using P = Point2D<int>;

	EXPECT_EQ(doubledArea(P(0, 0), P(0, 1), P(1, 0)), 1);
	EXPECT_EQ(doubledArea(P(0, 0), P(1, 0), P(0, 1)), 1);

	EXPECT_EQ(doubledArea(P(3, 5), P(-7, 8), P(-2, -1)), 75);
}

TEST(Point2D, TriangleAreaTestNoOverflow) {
	using P = Point2D<int32_t, int64_t>;
	EXPECT_EQ(doubledArea(P(0, 0), P(0, 1'000'000'000), P(1'000'000, 0)), 1'000'000'000'000'000);
}
