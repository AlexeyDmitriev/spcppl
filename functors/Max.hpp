#pragma once

#include <algorithm>

struct Max {
	template <typename T>
	T operator()(const T& l, const T& r) const {
		return std::max(l, r);
	}
};
