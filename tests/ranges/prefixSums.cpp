#include <gtest/gtest.h>
#include <spcppl/ranges/prefixSums.hpp>
#include <spcppl/ranges/fors.hpp>
#include <vector>
#include <set>

TEST(PrefixSumsTest, SumsVector) {
	std::vector<int> v = {4, 2, 7};
	EXPECT_EQ(prefixSums(v), (std::vector<int>{0, 4, 6, 13}));
}

TEST(PrefixSumsTest, SumsSet) {
	std::set<int> x = {1, 10, 100};
	EXPECT_EQ(prefixSums(x), (std::vector<int>{0, 1, 11, 111}));
}

TEST(PrefixSumsTest, SumsEmptyRange) {
	EXPECT_EQ(prefixSums(std::vector<int>{}), (std::vector<int>{0}));
}

TEST(PrefixSumsTest, SumsIntegerRange) {
	std::size_t len = 10;
	auto res = prefixSums(inclusiveRange(static_cast<std::size_t>(1), len));
	ASSERT_EQ(res.size(), len + 1);
	for (std::size_t i = 0; i <= len; ++i) {
		res[i] = i * (i + 1) / 2;
	}
}
