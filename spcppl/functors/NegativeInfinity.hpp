#pragma once

#include <limits>
#include <type_traits>

template <typename T, typename Enable = std::true_type>
struct NegativeInfinity;

template <typename T>
struct NegativeInfinity<T, typename std::is_integral<T>::type> {
	T operator()() const {
		return std::numeric_limits<T>::min();
	}
};

template <typename T>
struct NegativeInfinity<T, typename std::is_floating_point<T>::type> {
	T operator()() const {
		static_assert(std::numeric_limits<T>::has_infinity, "");
		return -std::numeric_limits<T>::infinity();
	}
};
