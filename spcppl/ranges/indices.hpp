#pragma once

#include <cstddef>
#include <vector>
#include <spcppl/assert.hpp>
#include <spcppl/ranges/fors.hpp>

template <typename T>
std::vector<T> indices(T n) {
	SPCPPL_ASSERT(n >= 0);
	std::vector<T> v(static_cast<std::size_t>(n));
	for (T i: range(n)) {
		v[static_cast<std::size_t>(i)] = i;
	}
	return v;
}
