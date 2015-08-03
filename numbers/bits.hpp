#pragma once

#include <cstddef>
#include "../assert.hpp"

template <typename T>
std::size_t leastSignificantBit(T number) {
	SPCPPL_ASSERT(number != 0);
	for (std::size_t i = 0;; ++i) {
		if ((number >> i) & 1)
			return i;
	}
}