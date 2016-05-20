#pragma once

#include "BottomUpSegmentTree.hpp"
#include "../../functors/Max.hpp"
#include "../../functors/NegativeInfinity.hpp"

template <typename T>
class BottomUpMaxSegmentTree: public BottomUpSegmentTree<T, Max<T>> {
public:
	template <typename R>
	BottomUpMaxSegmentTree(
			const R& range,
			const T& infinity = NegativeInfinity<T>()()
	): BottomUpSegmentTree<T, Max<T>>(range, infinity) {
	}

	void updateMaximum(std::size_t index, const T& value) {
		return this->update(index, [&value, this](T& element) {
			element = this->merge(element, value);
		});
	}

};
