#pragma once

#include <vector>
#include "assert.hpp"
#include "ranges/fors.hpp"
#include "numbers/bits.hpp"

template <typename T>
std::vector<T> submasksSums(std::vector<T> data) {
	SPCPPL_ASSERT(isPowerOf2(data.size()));

	for (std::size_t power = 1; power < data.size(); power *= 2) {
		for (std::size_t mask: range(data.size())) {
			if (mask & power) {
				data[mask] += data[mask ^ power];
			}
		}
	}
	return data;
}
