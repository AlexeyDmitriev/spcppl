#pragma once

#include <algorithm>
#include <limits>
#include <type_traits>
#include "BottomUpSegmentTree.hpp"
#include <spcppl/functors/Min.hpp>
#include <spcppl/functors/PositiveInfinity.hpp>

template <typename T>
class BottomUpMinSegmentTree: public BottomUpSegmentTree<T, Min> {
public:
	template <typename R>
	explicit BottomUpMinSegmentTree(
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
