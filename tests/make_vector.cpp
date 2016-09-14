#include <gtest/gtest.h>
#include <spcppl/make_vector.hpp>

TEST(MakeVector, MakeVector) {
	auto x = make_vector<int>(3, 5, 10, 20);

	ASSERT_EQ(x.size(), static_cast<std::size_t>(3));
	ASSERT_EQ(x[1].size(), static_cast<std::size_t>(5));
	ASSERT_EQ(x[1][4].size(), static_cast<std::size_t>(10));
	ASSERT_EQ(x[1][4][2], 20);
}
