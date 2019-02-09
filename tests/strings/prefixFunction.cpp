#include <gtest/gtest.h>
#include <spcppl/strings/prefixFunction.hpp>
#include <numeric>

TEST(PrefixFunctionTest, SimpleTest) {
	EXPECT_EQ(prefixFunction("abacaba"), (std::vector<std::size_t>{0, 0, 1, 0, 1, 2, 3}));
	EXPECT_EQ(prefixFunction("abc"), (std::vector<std::size_t>{0, 0, 0}));
}

TEST(PrefixFunctionTest, SameLettersTest) {
	size_t n = 123;
	std::vector<std::size_t> expected(123);
	std::iota(expected.begin(), expected.end(), 0);
	EXPECT_EQ(prefixFunction(std::string(n, 'x')), expected);
}

TEST(PrefixFunctionTest, SimpleSubstringTest) {
	EXPECT_TRUE(isSubstring("abacaba", "a"));
	EXPECT_FALSE(isSubstring("abacaba", "d"));
	EXPECT_TRUE(isSubstring("abacaba", "abac"));
	EXPECT_FALSE(isSubstring("abacaba", "abc"));
}

TEST(PrefixFunctionTest, SubstringInDifferentParts) {
	EXPECT_TRUE(isSubstring("abdfe", "ab"));
	EXPECT_TRUE(isSubstring("abfde", "de"));
	EXPECT_TRUE(isSubstring("abfde", "bfd"));
}

TEST(PrefixFunctionTest, SubstringDoesnFailAfterPartialMatch) {
	EXPECT_TRUE(isSubstring("ababac", "abac"));
}
