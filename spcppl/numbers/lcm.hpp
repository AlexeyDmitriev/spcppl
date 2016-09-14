#pragma once

#include "gcd.hpp"

template <typename T>
T lcm(const T& a, const T& b) {
	return a * b / gcd(a, b);
}