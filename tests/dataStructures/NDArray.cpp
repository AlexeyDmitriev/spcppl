#include <gtest/gtest.h>
#include <spcppl/dataStructures/NDArray.hpp>

TEST(NDArrayTest, Creation) {
	NDArray<int, 2> array({{3, 5}}, 0);
	EXPECT_EQ(array[0][1], 0);
}

TEST(NDArrayTest, Assignment) {
	NDArray<int, 2> array({{3, 5}}, 0);
	EXPECT_EQ(array[2][1], 0);

	array[2][1] = 1;

	EXPECT_EQ(array[0][0], 0);
	EXPECT_EQ(array[2][1], 1);
}

TEST(NDArrayTest, FrontBackTest) {
	NDArray<int, 3> array({{3, 5, 7}}, 1);
	array.back().front().back() = 5;
	EXPECT_EQ(array[2][0][6], 5);

	EXPECT_EQ(&array.back().front().back(), &array[2][0][6]);

	EXPECT_EQ(&array[1].back()[4], &array[1][4][4]);
}

TEST(NDArrayTest, AssignViewTest) {
	NDArray<int, 2> array({{2, 3}}, 0);
	array[0][0] = 1;
	array[0][1] = 2;
	array[1][0] = 3;
	array[1][1] = 4;
	array[2][0] = 5;
	array[2][1] = 6;

	assignView(array[2], array[1]);

	EXPECT_EQ(array[2][0], 3);
	EXPECT_EQ(array[2][1], 4);
	EXPECT_EQ(array[0][0], 1);
	EXPECT_EQ(array[0][1], 2);
	EXPECT_EQ(array[1][0], 3);
	EXPECT_EQ(array[1][1], 4);
}

TEST(NDArrayTest, CreateArrayTest) {
	auto array = makeArray<int>(5, 7, 2);
	EXPECT_EQ(array[3][2][1], 0);
	EXPECT_EQ(&array.back().back().back() - &array.front().front().front(), 5 * 7 * 2 - 1);

	auto filledArray = makeFilledArray<int>(42, 3, 2, 8);

	EXPECT_EQ(filledArray[1][1][1], 42);
	EXPECT_EQ(&filledArray.back().back().back() - &filledArray.front().front().front(), 3 * 2 * 8 - 1);
}
