#pragma once

#include <vector>
#include <cstddef>
#include "../identity.hpp"
#include "../typeTraits/enable_if_t.hpp"
#include "../ranges/fors.hpp"

template <typename T>
std::vector<T> factorials(std::size_t maxN) {
	std::vector<T> res(maxN + 1);
	res[0] = identity<T>();
	for (std::size_t i = 1; i <= maxN; ++i) {
		res[i] = res[i - 1] * static_cast<long long>(i);
	}
	return res;
}

template <typename T>
std::vector<std::vector<T>> binomials(std::size_t maxN) {
	std::vector<std::vector<T>> res(maxN + 1, std::vector<T>(maxN + 1));
	for (std::size_t n = 0; n <= maxN; ++n) {
		res[n][0] = identity<T>();
		res[n][n] = identity<T>();
		for (std::size_t k = 1; k < n; ++k) {
			res[n][k] = res[n - 1][k - 1] + res[n - 1][k];
		}
	}

	return res;
}

template <typename T, typename U, typename = enable_if_t<std::is_integral<U>::value>>
T binomial(U n, U k) {
	if (k > n || k < 0) {
		return T();
	}
	T res = identity<T>();
	for (U i: inclusiveRange(1, k)) {
		res *= n - i + 1;
		res /= i;
	}
	return res;
};

template <typename T, typename U, typename = enable_if_t<std::is_integral<U>::value>>
T starsAndBars(U stars, U groups) {
	if (groups == 0) {
		if (stars == 0) {
			return identity<T>();
		} else {
			return T();
		}
	}
	return binomial<T>(stars + groups - 1, groups - 1);
};
