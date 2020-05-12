#include <gtest/gtest.h>
#include <spcppl/geometry/convexHull.hpp>

using Point = Point2D<int>;

TEST(ConvexHullTest, SamePointsInCounterClockwiseOrderForSquare) {
	std::vector<Point> points = {
			{0, 0},
			{1, 1},
			{0, 1},
			{1, 0},
	};
	std::vector<Point> expected = {
			{0, 0},
			{1, 0},
			{1, 1},
			{0, 1},
	};
	EXPECT_EQ(convexHull(points), expected);
}

TEST(ConvexHullTest, CentralPointDisappears) {
	std::vector<Point> points = {
			{0, 0},
			{2, 2},
			{1, 1},
			{2, 0},
			{0, 2},
	};
	std::vector<Point> expected = {
			{0, 0},
			{2, 0},
			{2, 2},
			{0, 2},
	};
	EXPECT_EQ(convexHull(points), expected);
}

TEST(ConvexHullTest, PointOnTheEdgeDisappears) {
	std::vector<Point> points = {
			{0, 2},
			{2, 0},
			{0, 0},
			{2, 2},
			{1, 2},
	};
	std::vector<Point> expected = {
			{0, 0},
			{2, 0},
			{2, 2},
			{0, 2},
	};
	EXPECT_EQ(convexHull(points), expected);
}

TEST(ConvexHullTest, ConvexHullOnIndices) {
	std::vector<Point> points = {
			{0, 0},
			{2, 2},
			{1, 2},
			{0, 2},
			{2, 0},
	};
	std::vector<int> indices({0, 1, 2, 3, 4});
	std::vector<int> expectedIndices = {0, 4, 1, 3};

	auto actual = convexHull(indices, [&](int i) {
		return points[i];
	});
	EXPECT_EQ(actual, expectedIndices);
}
