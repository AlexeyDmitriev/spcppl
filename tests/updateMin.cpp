#include <gtest/gtest.h>
#include <spcppl/updateMin.hpp>

TEST(UpdateMinTest, UpdatesWhenSmaller) {
	int a = 5;
	updateMin(a, 3);
	EXPECT_EQ(a, 3);
}

TEST(UpdateMinTest, LeavesWhenGreater) {
	int a = 7;
	updateMin(a, 10);
	EXPECT_EQ(a, 7);
}

TEST(UpdateMaxTest, UpdatesWhenGreater) {
	int a = 7;
	updateMax(a, 10);
	EXPECT_EQ(a, 10);
}

TEST(UpdateMaxTest, LeavesOldWhenSmaller) {
	int a = 5;
	updateMax(a, 3);
	EXPECT_EQ(a, 5);
}
