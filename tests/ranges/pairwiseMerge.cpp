#include <vector>
#include <functional>
#include <gtest/gtest.h>
#include <spcppl/ranges/pairwiseMerge.hpp>

TEST(PairwiseMerge, Unique) {
	std::vector<int> v = {3, 5, 7, 7, 5, 5, 5, 5};
	pairwiseMerge(v, std::equal_to<>());
	EXPECT_EQ(v, (std::vector<int>{3, 5, 7, 5}));
}

TEST(PairwiseMerge, Empty) {
	std::vector<int> v;
	pairwiseMerge(v, std::equal_to<>());
	EXPECT_TRUE(v.empty());
}

TEST(PairwiseMerge, OneElement) {
	std::vector<int> v = {42};
	auto v_original = v;
	pairwiseMerge(v, std::equal_to<>());
	EXPECT_EQ(v, v_original);
}

TEST(PairwiseMerge, CalcualteSum) {
	std::vector<int> v = {3, 2, 5, 42};
	pairwiseMerge(v, [](int& l, int r) {
		l += r;
		return true;
	});
	EXPECT_EQ(v, std::vector<int>{52});
}

TEST(PairwiseMerge, MergeSegments) {
	using Segment = std::pair<int, int>;
	std::vector<Segment> v = {{0, 1}, {1, 5}, {7, 10}, {10, 12}, {12, 15}, {20, 21}};
	auto merge_segments = [&](Segment& l, const Segment& r) {
		if (l.second == r.first) {
			l.second = r.second;
			return true;
		}
		return false;
	};

	pairwiseMerge(v, merge_segments);
	EXPECT_EQ(v, (std::vector<Segment>{{0, 5}, {7, 15}, {20, 21}}));
}
