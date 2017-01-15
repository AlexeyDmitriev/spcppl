#pragma once

#include <spcppl/assert.hpp>

template <typename T>
T divideCeil(T a, T b) {
	SPCPPL_ASSERT(b != 0);
	if (b < 0) {
		a = -a;
		b = -b;
	}
	return a / b + (a % b > 0);
}

template <typename T>
T divideFloor(T a, T b) {
	SPCPPL_ASSERT(b != 0);
	if (b < 0) {
		a = -a;
		b = -b;
	}
	return a / b - (a % b < 0);
}

template <typename T>
T divideTowardsZero(T a, T b) {
	SPCPPL_ASSERT(b != 0);
	return a / b;
}

template <typename T>
T divideAwayFromZero(T a, T b) {
	SPCPPL_ASSERT(b != 0);
	bool changeSign = false;
	if (a < 0) {
		changeSign = !changeSign;
		a = -a;
	}
	if (b < 0) {
		changeSign = !changeSign;
		b = -b;
	}
	T res = (a + b - 1) / b;
	if (changeSign) {
		res *= -1;
	}
	return res;
}

