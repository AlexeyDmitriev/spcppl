#pragma once

#include <vector>
#include <spcppl/ranges/wrappers.hpp>

template <typename T>
std::vector<T> unsortedDivisors(const T& n) {
	std::vector<T> result;
	for (int i = 1; i * i <= n; ++i) {
		if (n % i == 0) {
			result.push_back(i);
			if (i * i != n) {
				result.push_back(n / i);
			}
		}
	}
	return result;
}

template <typename T>
std::vector<T> sortedDivisors(const T& n) {
	return sorted(unsortedDivisors(n));
}
