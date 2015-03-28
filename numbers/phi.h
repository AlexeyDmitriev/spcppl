#pragma once

template <typename T>
T phi(T x) {
	T result = x;
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0) {
			result /= i;
			result *= i - 1;
			while (x % i == 0) {
				x /= i;
			}
		}
	}
	if (x > 1) {
		result /= x;
		result *= x - 1;
	}
	return result;
}