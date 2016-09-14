#include <gtest/gtest.h>
#include <spcppl/CoordinateMinimizer.hpp>
#include <vector>
#include <string>

TEST(CoordinateMinimizer, Basic) {
	std::vector<int> v{10, 7, 12};
	CoordinateMinimizer<int> minimizer(v);
	ASSERT_EQ(minimizer.find(7), static_cast<std::size_t>(0));
	ASSERT_EQ(minimizer.find(12), static_cast<std::size_t>(2));
	ASSERT_EQ(minimizer.find(10), static_cast<std::size_t>(1));
}

TEST(CoordinateMinimizer, Stings) {
	std::vector<std::string> v{"abc", "zzz", "z", "x"};
	CoordinateMinimizer<std::string> minimizer(v);
	ASSERT_EQ(minimizer.find("abc"), static_cast<std::size_t>(0));
	ASSERT_EQ(minimizer.find("x"), static_cast<std::size_t>(1));
	ASSERT_EQ(minimizer.find("z"), static_cast<std::size_t>(2));
	ASSERT_EQ(minimizer.find("zzz"), static_cast<std::size_t>(3));
}

TEST(CoordinateMinimizer, OneByOne) {
	CoordinateMinimizer<int> minimizer;
	minimizer.add(5);
	minimizer.add(3);
	minimizer.add(10);
	minimizer.finalize();
	ASSERT_EQ(minimizer.find(3), static_cast<std::size_t>(0));
	ASSERT_EQ(minimizer.find(5), static_cast<std::size_t>(1));
	ASSERT_EQ(minimizer.find(10), static_cast<std::size_t>(2));
}
