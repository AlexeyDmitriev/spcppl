#pragma once

#include <spcppl/dataStructures/segmentTree/BottomUpSegmentTree.hpp>
#include <spcppl/functors/Max.hpp>
#include <spcppl/functors/NegativeInfinity.hpp>

template <typename T>
class BottomUpMaxSegmentTree: public BottomUpSegmentTree<T, Max> {
public:
	template <typename R>
	explicit BottomUpMaxSegmentTree(
			const R& range,
			const T& infinity = NegativeInfinity<T>()()
	): BottomUpSegmentTree<T, Max>(range, infinity) {
	}

	void updateMaximum(std::size_t index, const T& value) {
		return this->update(index, [&value, this](T& element) {
			element = this->merge(element, value);
		});
	}

};
