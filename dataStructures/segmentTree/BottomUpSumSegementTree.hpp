#pragma once

#include <algorithm>
#include <limits>
#include <type_traits>
#include "BottomUpSegmentTree.hpp"

template <typename T>
class BottomUpSumSegmentTree :
		public BottomUpSegmentTree<T, std::plus<T>> {
public:
	BottomUpSumSegmentTree(
			std::size_t n,
			const T& zero = T()
	) : BottomUpSegmentTree<T, std::plus<T>>(n, zero) {
	}

	template <typename R>
	BottomUpSumSegmentTree(
			const R& range,
			const T& zero = T()
	) : BottomUpSegmentTree<T, std::plus<T>>(range, zero) {
	}

};