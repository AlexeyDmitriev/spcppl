#pragma once

#include <spcppl/binpow.hpp>

template <typename T>
T geometricProgrssionSum(T first, T q, long long n) {
	if (q == 1) {
		return first * n;
	}
	return first * (1 - binpow(q, n)) / (1 - q);
}

template <typename T>
T inifiniteGeometricProgressionSum(T first, T q) {
	SPCPPL_ASSERT(-1 < q && q < 1);
	return first / (1 - q);
}
