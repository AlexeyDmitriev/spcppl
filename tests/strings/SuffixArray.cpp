#include <gtest/gtest.h>
#include <spcppl/strings/SuffixArray.hpp>
#include <spcppl/ranges/wrappers.hpp>
#include <string>
#include <cstddef>
#include <random>

TEST(SuffixArray, NthSuffix) {
	SuffixArray suffixArray("abacaba");
	ASSERT_EQ(suffixArray.getNthSuffix(0), static_cast<std::size_t>(6));
	ASSERT_EQ(suffixArray.getNthSuffix(4), static_cast<std::size_t>(5));
	ASSERT_EQ(suffixArray.getNthSuffix(6), static_cast<std::size_t>(3));

	ASSERT_EQ(suffixArray.getPosition(0), static_cast<std::size_t>(2));
	ASSERT_EQ(suffixArray.getPosition(1), static_cast<std::size_t>(5));
	ASSERT_EQ(suffixArray.getPosition(2), static_cast<std::size_t>(3));
	ASSERT_EQ(suffixArray.getPosition(4), static_cast<std::size_t>(1));
}

TEST(SuffixArray, EmptyNoFail) {
	SuffixArray suffixArray("");
}

TEST(SuffixArray, Single) {
	SuffixArray suffixArray("x");
	ASSERT_EQ(suffixArray.getNthSuffix(0), static_cast<std::size_t>(0));
	ASSERT_EQ(suffixArray.getPosition(0), static_cast<std::size_t>(0));
}

TEST(SuffixArray, Big) {
	std::mt19937 gen;
	std::size_t n = 100;
	std::string string(n, ' ');
	std::uniform_int_distribution<char> dist('A', 'Z');
	
	for (std::size_t i = 0; i < n; ++i) {
		string[i] = dist(gen);
	}
	
	SuffixArray suffixArray(string);
	std::vector<std::size_t> indicies(n);
	for (std::size_t i = 0; i < n; ++i) {
		indicies[i] = i;
	}

	std::sort(indicies.begin(), indicies.end(), [&](std::size_t l, std::size_t r) {
		return string.substr(l) < string.substr(r);
	});

	for (std::size_t i = 0; i < n; ++i) {
		ASSERT_EQ(suffixArray.getNthSuffix(i), indicies[i]) << "i: " << i;
		ASSERT_EQ(suffixArray.getPosition(indicies[i]), i) << "i: " << i;
	}
}

