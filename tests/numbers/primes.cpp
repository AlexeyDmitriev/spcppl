#include <spcppl/numbers/primes.hpp>
#include <gtest/gtest.h>
#include <span>

namespace {
const std::vector<int> smallPrimes = {2, 3, 5, 7};
}

TEST(PrimesTest, PrimeMapOnRange) {
	EXPECT_EQ(primeMapOnRange(11, 14, smallPrimes), (std::vector<Bool>{true, false, true}));
	{
		auto allMap = primeMap(19);
		EXPECT_EQ(primeMapOnRange(10, 20, smallPrimes), (std::vector<Bool>{allMap.begin() + 10, allMap.end()}));
	}
}

TEST(PrimesTest, PrimesOnRange) {
	EXPECT_EQ(primesOnRange(11, 14, smallPrimes), (std::vector<int>{11, 13}));
	EXPECT_EQ(primesOnRange(1, 10, smallPrimes), smallPrimes);
}

TEST(PrimesTest, PrimesOnRangeDoesntIncludeLast) {
	EXPECT_EQ(primesOnRange(11, 13, smallPrimes), (std::vector<int>{11}));
}

TEST(PrimesTest, PrimeMapOnRangeWorksForBig) {
	int64_t begin = 1'000'000'000'000;
	int64_t end = 1'000'000'001'000;
	auto map = primeMapOnRange(begin, end, allPrimes(1'100'000));
	for (auto x: range(begin, end)) {
		EXPECT_EQ(map[x - begin], isPrime(x)) << "x: " << x;
	}
}
