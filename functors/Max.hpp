#pragma once

#include <algorithm>

template <typename T>
struct Max {
	T operator()(const T& l, const T& r) const {
		return std::max(l, r);
	}
};
