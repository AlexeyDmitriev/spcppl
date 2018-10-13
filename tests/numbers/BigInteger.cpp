#include <spcppl/numbers/BigInteger.hpp>
#include <gtest/gtest.h>
#include <spcppl/ranges/fors.hpp>
#include <random>
#include <sstream>


TEST(BigInteger, Equality) {
	EXPECT_EQ(BigInteger("0"), BigInteger("0"));
	EXPECT_NE(BigInteger("0"), BigInteger("1"));
}

TEST(BigInteger, Comparisons) {
	EXPECT_LT(BigInteger("0"), BigInteger("1"));
	EXPECT_LT(BigInteger("9"), BigInteger("10"));

	EXPECT_GT(BigInteger("321"), BigInteger("199"));

	EXPECT_GT(BigInteger( "1000000000000000000000"), BigInteger("100000000000000000000"));
	EXPECT_LT(BigInteger("-1000000000000000000000"), BigInteger("100000000000000000000"));
}

TEST(BigInteger, DefaultConstruction) {
	EXPECT_EQ(BigInteger("0"), BigInteger());
}

TEST(BigInteger, Negatives) {
	EXPECT_EQ(BigInteger("-0"), BigInteger("0"));
	EXPECT_NE(BigInteger("-5"), BigInteger("5"));
	EXPECT_LT(BigInteger("-5"), BigInteger("0"));
}

TEST(BigInteger, LeadingZeros) {
	EXPECT_EQ(BigInteger("007"), BigInteger("7"));
	EXPECT_EQ(BigInteger("00"), BigInteger("0"));
	EXPECT_EQ(BigInteger("-0000"), BigInteger("0"));
	EXPECT_EQ(BigInteger("-0000005"), BigInteger("-5"));
}

std::string to_string(const BigInteger& rhs) {
	std::ostringstream ss;
	ss << rhs;
	return ss.str();
}

TEST(BigInteger, PreservesString) {
	std::mt19937 rnd;
	for (auto _ [[maybe_unused]]: range(100)) {
		std::string string;
		auto length = std::uniform_int_distribution<std::size_t>(1, 1000)(rnd);
		for (auto index: range(length)) {
			string += std::uniform_int_distribution<char>(index == 0 ? '1' : '0', '9')(rnd);
		}
		if (!string.empty()) {
			EXPECT_EQ(string, to_string(BigInteger(string)));
		}
	}
}

TEST(BigInteger, ConstructionFromInteger) {
	EXPECT_EQ(BigInteger("5"), BigInteger(5));
	EXPECT_EQ(BigInteger("-17"), BigInteger(-17));

	EXPECT_EQ(BigInteger(2u), BigInteger(2));
	EXPECT_EQ(BigInteger(123456789987654321LL), BigInteger("123456789987654321"));
}

TEST(BigInteger, ConstructionFromCornerCases) {
	EXPECT_EQ(BigInteger("-2147483648"), BigInteger(std::numeric_limits<int32_t>::min()));
	EXPECT_EQ(BigInteger("2147483647"), BigInteger(std::numeric_limits<int32_t>::max()));
	EXPECT_EQ(BigInteger("-9223372036854775808"), BigInteger(std::numeric_limits<int64_t>::min()));
	EXPECT_EQ(BigInteger("9223372036854775807"), BigInteger(std::numeric_limits<int64_t>::max()));
}

TEST(BigInteger, Addition) {
	EXPECT_EQ(BigInteger(2) + BigInteger(3), BigInteger(5));
	EXPECT_EQ(BigInteger(5) + BigInteger(-5), BigInteger());
	EXPECT_EQ(BigInteger("-123482748923748923748923748932748923748923") + BigInteger("123482748923748923748923748932748923748923"), BigInteger());
	EXPECT_EQ(BigInteger("999999999999999") + BigInteger(1), BigInteger("1000000000000000"));
	EXPECT_EQ(BigInteger(1) + BigInteger("999999999999999"), BigInteger("1000000000000000"));
}

TEST(BigInteger, Multiplication) {
	EXPECT_EQ(BigInteger("2") * 3, BigInteger("6"));
	EXPECT_EQ(BigInteger("2") * BigInteger("3"), BigInteger("6"));
	EXPECT_EQ(2LL * BigInteger("3"), BigInteger("6"));
	EXPECT_EQ(BigInteger(100000) * BigInteger(100000), BigInteger(10'000'000'000LL));

	EXPECT_EQ(
			BigInteger("4785974389573489572489758937589347589347589347589347589347589432758934") * BigInteger("458094758943758923748923647236478326478236748236784236784643785634786578246597243"),
			BigInteger("2192429784302671467919007921697750410148554848247894746582207779373105073375035215686871375677131908065225960777754019816604326597006535602139008018962")
	);

	EXPECT_EQ(
			BigInteger("72859743895789243758952387534789543789573489578934745894") * 57,
			BigInteger("4153005402059986894260286089483003996005688905999280515958")
	);
}
