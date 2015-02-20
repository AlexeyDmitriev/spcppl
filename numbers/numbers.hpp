#pragma once

#include <vector>
#include <cstddef>
#include "../identity.hpp"

template <typename T>
std::vector<T> impl__factorials(size_t maxN, const T& one) {
	std::vector<T> res(maxN + 1);
	res[0] = one;
	for (size_t i = 1; i <= maxN; ++i) {
		res[i] = res[i - 1] * i;
	}
	return res;
}

template <typename T>
std::vector<T> factorials(size_t maxN) {
	return impl__factorials(maxN, identity<T>());
}

template <typename T>
std::vector<T> factorials(size_t maxN, const T& sample) {
	return impl__factorials(maxN, identity<T>(sample));

}
