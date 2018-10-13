#pragma once

#include <functional>
#include "TopDownSegementTree.hpp"

template <typename T>
struct SumUpdateApplier {
	T operator()(const T& value, const T& update, std::size_t l, std::size_t r) const {
		return value + update * (r - l);
	}
};

template <typename T>
class TopDownSumSegmentTree:
		public TopDownSegmentTree<T, std::plus<T>, T, SumUpdateApplier<T>, std::plus<T>> {
public:
	template <typename R>
	explicit TopDownSumSegmentTree(
			const R& range,
			const T& zero = T()
	): TopDownSegmentTree<T, std::plus<T>, T, SumUpdateApplier<T>, std::plus<T>>(range, zero) {
	}

};
