#pragma once

template <typename T>
T gcd(T a, T b) {
	while (b) {
		T tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}