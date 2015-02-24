#pragma once

#include <vector>
#include <cstddef>

bool isPrime(int n) {
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return n >= 2;
}

struct Bool {
	/* implicit */ Bool(bool value) : value(value) {

	}

	operator bool() const {
		return value;
	}

private:
	bool value;
};

std::vector<Bool> primeMap(size_t maxN) {
	std::vector<Bool> prime(maxN + 1, true);

	prime[0] = false;
	prime[1] = false;

	for (size_t i = 2; i * i <= maxN; ++i) {
		if (prime[i]) {
			if (i * 1ULL * i <= maxN) {
				for (size_t j = i * i; j <= maxN; j += i) {
					prime[j] = false;
				}
			}
		}
	}
	return prime;
}
