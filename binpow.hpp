#pragma once

#include "identity.hpp"
#include "assert.hpp"

template <typename T>
T binpow(T base, long long power) {
	SPCPPL_ASSERT(power >= 0);
	T result = identity<T>();
	while (power > 0) {
		if (power & 1) {
			result *= base;
		}
		power >>= 1;
		base *= base;
	}
	return result;
}
