#include <spcppl/dataStructures/SparseTable.hpp>
#include <spcppl/functors/Min.hpp>
#include <spcppl/numbers/gcd.hpp>
#include <gtest/gtest.h>
#include <spcppl/functors/PositiveInfinity.hpp>

TEST(SparseTableTest, GetMinimumCorrectly) {
	std::vector<int> elements {5, 3, 2, 7, 4};
	SparseTable<int, Min> sparse(elements);

	EXPECT_EQ(sparse.getResult(2, 5), 2);
	EXPECT_EQ(sparse.getResult(0, 2), 3);
	EXPECT_EQ(sparse.getResult(3, 4), 7);
}

TEST(SparseTableTest, WorksWithNonStandardOperatoins) {
	struct GCD {
		int operator() (int a, int b) const {
			return gcd(a, b);
		}
	};
	std::vector<int> elements = {8, 5, 15, 9, 12};
	SparseTable<int, GCD> sparse(elements);
	EXPECT_EQ(sparse.getResult(2, 5), 3);
	EXPECT_EQ(sparse.getResult(0, 1), 8);
	EXPECT_EQ(sparse.getResult(0, 5), 1);
	EXPECT_EQ(sparse.getResult(0, 0), 0);
}

TEST(SparseTable, WorksWithEmptyRanges) {
	std::vector<int> elements = {};
	SparseTable<int, Min> sparse(elements, Min(), PositiveInfinity<int>()());
	EXPECT_EQ(sparse.getResult(0, 0), PositiveInfinity<int>()());
}

TEST(SparseTable, WorksWithSingleton) {
	SparseTable<int, Min> sparse({1});

	EXPECT_EQ(sparse.getResult(0, 1), 1);
}
