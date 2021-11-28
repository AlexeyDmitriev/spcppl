#pragma once

#include <vector>
#include <cstddef>
#include <spcppl/assert.hpp>
#include <spcppl/numbers/division.hpp>
#include <spcppl/ranges/fors.hpp>
#include <spcppl/Bool.hpp>

inline bool isPrime(int n) {
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return n >= 2;
}

inline bool isPrime(int64_t n) {
	for (int64_t i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return n >= 2;
}

inline std::vector<Bool> primeMap(std::size_t maxN) {
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

inline std::vector<int> allPrimes(int maxN) {
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

inline int nextPrime(int n) {
	while (!isPrime(n)) {
		++n;
	}
	return n;
}

inline int64_t nextPrime(int64_t n) {
	while (!isPrime(n)) {
		++n;
	}
	return n;
}

/*
 * It needs primes up to sqrt(r - 1)
 */
template <typename T>
std::vector<Bool> primeMapOnRange(T l, T r, const std::vector<int>& primes) {
	SPCPPL_ASSERT(l > 0);
	std::vector<Bool> prime(static_cast<std::size_t>(r - l), true);
	if (l == 1) {
		prime[0] = false;
	}
	for (int p: primes) {
		if (static_cast<int64_t>(p) * p > r) {
			break;
		}
		T start_idx = divideCeil(l, static_cast<T>(p));
		if (start_idx < 2) {
			start_idx = 2;
		}
		for (auto j = static_cast<size_t>(start_idx * p - l); j < prime.size(); j += p) {
			prime[j] = false;
		}
	}
	return prime;
}

template <typename T>
std::vector<T> primesOnRange(T l, T r, const std::vector<int>& primes) {
	auto primeMap = primeMapOnRange(l, r, primes);
	std::vector<T> result;
	for (std::size_t i = 0; i < primeMap.size(); ++i) {
		if (primeMap[i]) {
			result.push_back(static_cast<T>(i + l));
		}
	}
	return result;
}
