#pragma once

#include <functional>
#include "BottomUpSegmentTree.hpp"

template <typename T>
class BottomUpSumSegmentTree: public BottomUpSegmentTree<T, std::plus<T>> {
public:
	template <typename R>
	explicit BottomUpSumSegmentTree(
			const R& range,
			const T& zero = T()
	): BottomUpSegmentTree<T, std::plus<T>>(range, zero) {
	}

};
