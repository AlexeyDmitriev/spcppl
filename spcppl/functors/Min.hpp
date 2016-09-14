#pragma once

#include <algorithm>
struct Min {
	template <typename T>
	T operator()(const T& l, const T& r) const {
		return std::min(l, r);
	}
};
