#pragma once

#include <algorithm>
#include <limits>
#include <type_traits>
#include "BottomUpSegmentTree.hpp"

template <typename T>
struct Max {
	T operator ()(const T& l, const T& r) const {
		return std::max(l, r);
	}
};

//FIXME: remove {} when CPP-1825 fixed.
template <typename T, typename Enable = std::true_type>
struct NegativeInfinity {
	T operator ()() const;
};

template <typename T>
struct NegativeInfinity<T, typename std::is_integral<T>::type> {
	T operator ()() const {
		return std::numeric_limits<T>::max();
	}
};

template <typename T>
struct NegativeInfinity<T, typename std::is_floating_point<T>::type> {
	T operator ()() const {
		return std::numeric_limits<T>::infinity();
	}
};

template <typename T>
class BottomUpMaxSegmentTree :
		public BottomUpSegmentTree<T, Max<T>> {
public:
	BottomUpMaxSegmentTree(
			std::size_t n,
			const T& infinity = NegativeInfinity<T>()
	) : BottomUpSegmentTree<T, Max<T>>(n, infinity) {
	}

	template <typename R>
	BottomUpMaxSegmentTree(
			const R& range,
			const T& infinity = NegativeInfinity<T>()()
	) : BottomUpSegmentTree<T, Max<T>>(range, infinity) {
	}

	void updateMaximum(std::size_t index, const T& value) {
		return update(index, [&value](T& element) {
		    element = merge(element, value);
		});
	}

};