#pragma once

#include <vector>
#include <cstddef>
#include "../identity.hpp"

template <typename T>
std::vector<T> impl__factorials(std::size_t maxN, const T& one) {
	std::vector<T> res(maxN + 1);
	res[0] = one;
	for (std::size_t i = 1; i <= maxN; ++i) {
		res[i] = res[i - 1] * i;
	}
	return res;
}

template <typename T>
std::vector<T> factorials(std::size_t maxN) {
	return impl__factorials(maxN, identity<T>());
}

template <typename T>
std::vector<T> factorials(std::size_t maxN, const T& sample) {
	return impl__factorials(maxN, identity<T>(sample));
}


template <typename T>
std::vector<std::vector<T>> impl__binomials(std::size_t maxN, const T& one) {
	std::vector<std::vector<T>> res(maxN + 1, std::vector<T>(maxN + 1));
	for (std::size_t n = 0; n <= maxN; ++n) {
		res[n][0] = one;
		res[n][n] = one;
		for (std::size_t k = 1; k < n; ++k) {
			res[n][k] = res[n - 1][k - 1] + res[n - 1][k];
		}
	}

	return res;
}

template <typename T>
std::vector<std::vector<T>> binomials(std::size_t maxN) {
	return impl__binomials(maxN, identity<T>());
}

template <typename T>
std::vector<std::vector<T>> binomials(std::size_t maxN, const T& sample) {
	return impl__binomials(maxN, identity<T>(sample));
}
