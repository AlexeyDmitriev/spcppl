#include <gtest/gtest.h>
#include <map>
#include <spcppl/parallel.hpp>
#include <spcppl/numbers/division.hpp>

template <typename T>
std::ptrdiff_t rangeSize(IntegerRange<T> range) {
	return std::distance(range.begin(), range.end());
}

TEST(WorkerRange, EqualParts) {
	for (int i = 0; i < 5; ++i) {
		ASSERT_EQ(rangeSize(workerRange(10, i, 5)), 2);
	}
}

TEST(WorkerRange, UnequalParts) {
	int size = 27;
	int nodes = 5;
	for (int i = 0; i < nodes; ++i) {
		auto workerRangeSize = rangeSize(workerRange(size, i, nodes));
		ASSERT_GE(workerRangeSize, divideFloor(size, nodes)) << "node: " << i;
		ASSERT_LE(workerRangeSize, divideCeil(size, nodes)) << "node: " << i;
	}
}

TEST(WorkerRange, EverythingOne) {
	std::map<int, int> usedCount;
	int size = 27;
	int nodes = 5;
	for (int node = 0; node < nodes; ++node) {
		for (int x: workerRange(size, node, nodes)) {
			++usedCount[x];
		}
	}
	ASSERT_EQ(usedCount.size(), static_cast<size_t>(size));
	for (int i = 0; i < size; ++i) {
		ASSERT_EQ(usedCount[i], 1) << "i: " << i;
	}
}

TEST(WorkerRange, OneNode) {
	ASSERT_EQ(*workerRange(5, 0, 1).begin(), 0);
	ASSERT_EQ(*workerRange(5, 0, 1).end(), 5);
}

TEST(WorkerRange, EmptyRange) {
	ASSERT_EQ(workerRange(0, 7, 10).begin(), workerRange(0, 7, 10).end());
}
