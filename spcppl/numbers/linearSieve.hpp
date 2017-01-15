#pragma once

#include <vector>
#include <spcppl/assert.hpp>

std::vector<int> linearSieve(int maxN) {
	SPCPPL_ASSERT(maxN > 0);
	std::vector<int> leastPrimes(maxN + 1);
	std::vector<int> primes;

	for (int i = 2; i <= maxN; ++i) {
		if (leastPrimes[i] == 0) {
			leastPrimes[i] = i;
			primes.push_back(i);
		}
		for (int prime: primes) {
			if (i * prime > maxN) {
				break;
			}
			leastPrimes[i * prime] = prime;
		}
	}
	return leastPrimes;
}
