#pragma once

#include <functional>
#include <cstddef>
#include "LazyPointSegmentTree.hpp"

template <typename T>
class LazySumSegmentTree: public LazyPointSegmentTree<T, std::plus<T>> {
public:
	template <typename R>
	explicit LazySumSegmentTree(
			std::size_t n,
			const T& zero = T()
	): LazyPointSegmentTree<T, std::plus<T>>(n, zero) {
	}

};
