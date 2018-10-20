#pragma once

#include <vector>
#include <cstddef>
#include <spcppl/ranges/fors.hpp>
#include <spcppl/Bool.hpp>

bool isPrime(int n) {
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return n >= 2;
}

bool isPrime(int64_t n) {
	for (int64_t i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return n >= 2;
}

std::vector<Bool> primeMap(std::size_t maxN) {
	std::vector<Bool> prime(maxN + 1, true);

	prime[0] = false;
	prime[1] = false;

	for (std::size_t i = 2; i * i <= maxN; ++i) {
		if (prime[i]) {
			if (i * 1ULL * i <= maxN) {
				for (std::size_t j = i * i; j <= maxN; j += i) {
					prime[j] = false;
				}
			}
		}
	}
	return prime;
}

std::vector<int> allPrimes(int maxN) {
	std::vector<int> result;
	result.reserve(maxN);
	std::vector<Bool> map = primeMap(maxN);
	for (int i: range(maxN + 1)) {
		if (map[i]) {
			result.push_back(i);
		}
	}
	return result;
}

int nextPrime(int n) {
	while (!isPrime(n)) {
		++n;
	}
	return n;
}
