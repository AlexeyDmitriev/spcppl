#pragma once

#include <algorithm>
#include <limits>
#include <type_traits>
#include "BottomUpSegmentTree.hpp"
#include "../../functors/Min.hpp"

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

template <typename T>
class BottomUpMinSegmentTree: public BottomUpSegmentTree<T, Min> {
public:
	template <typename R>
	BottomUpMinSegmentTree(
			const R& range,
			const T& infinity = PositiveInfinity<T>()()
	): BottomUpSegmentTree<T, Min>(range, infinity) {
	}

	void updateMinimum(std::size_t index, const T& value) {
		return this->update(index, [&value, this](T& element) {
			element = this->merge(element, value);
		});
	}

};
