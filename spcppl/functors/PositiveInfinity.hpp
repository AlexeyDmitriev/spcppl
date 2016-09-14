#pragma once

#include <type_traits>
#include <limits>

//FIXME: remove {} when CPP-1825 fixed.
template <typename T, typename Enable = std::true_type>
struct PositiveInfinity {
	T operator()() const;
};

template <typename T>
struct PositiveInfinity<T, typename std::is_integral<T>::type> {
	T operator()() const {
		return std::numeric_limits<T>::max();
	}
};

template <typename T>
struct PositiveInfinity<T, typename std::is_floating_point<T>::type> {
	T operator()() const {
		return std::numeric_limits<T>::infinity();
	}
};
