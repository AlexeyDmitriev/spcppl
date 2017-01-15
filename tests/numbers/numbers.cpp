#include <spcppl/numbers/numbers.hpp>
#include <spcppl/numbers/Zn.hpp>
#include <gtest/gtest.h>

TEST(NumbersTest, FactorialTest) {
	EXPECT_EQ(factorial<int>(0), 1);
	EXPECT_EQ(factorial<int>(1), 1);
	EXPECT_EQ(factorial<int>(2), 2);
	EXPECT_EQ(factorial<int>(5), 120);

	using Z = ZnConst<97>;
	EXPECT_EQ(factorial<Z>(100), Z());
}

TEST(NumberTest, FactorialsTest) {
	EXPECT_EQ(factorials<int>(0), std::vector<int>{1});
	EXPECT_EQ(factorials<int>(5), (std::vector<int>{1, 1, 2, 6, 24, 120}));
}

TEST(NumbersTest, BinomialTest) {
	EXPECT_EQ(binomial<int>(0, 0), 1);
	EXPECT_EQ(binomial<int>(5, 3), 10);
	EXPECT_EQ(binomial<int>(10, 10), 1);
}

TEST(NumbersTest, PascalTriangleRowTest) {
	using Result = std::vector<int>;
	EXPECT_EQ(pascalTriangleRow<int>(0), Result{1});
	EXPECT_EQ(pascalTriangleRow<int>(1), (Result{1, 1}));
	EXPECT_EQ(pascalTriangleRow<int>(5), (Result{1, 5, 10, 10, 5, 1}));

	EXPECT_EQ(pascalTriangleRow<int>(2, 5), (Result{1, 2, 1, 0, 0, 0}));
	EXPECT_EQ(pascalTriangleRow<int>(10, 2), (Result{1, 10, 45}));
}

TEST(NumbersTest, BinomialsTest) {
	auto result = binomials<int>(5);
	ASSERT_EQ(result.size(), static_cast<size_t>(6));
	for (int i = 0; i <= 5; ++i) {
		ASSERT_EQ(result[i].size(), static_cast<size_t>(6)) << "i: " << i;
		for (int j = 0; j <= i; ++j) {
			EXPECT_EQ(result[i][j], binomial<int>(i, j)) << "i: " << i << " j:" << j;
		}
	}
}

TEST(NumbersTest, StarsAndBars) {
	EXPECT_EQ(starsAndBars<int>(0, 0), 1);
	EXPECT_EQ(starsAndBars<int>(5, 1), 1);
	EXPECT_EQ(starsAndBars<int>(5, 2), 6);
	EXPECT_EQ(starsAndBars<int>(1, 12), 12);
}
