#pragma once

#include <vector>
#include <numeric>

template <typename R>
auto prefixSums(const R& range) -> std::vector<typename R::value_type> {
	std::vector<typename R::value_type> result(
			static_cast<std::size_t>(
					std::distance(std::begin(range), std::end(range)) + 1
			)
	);
	std::partial_sum(std::begin(range), std::end(range), result.begin() + 1);
	return result;
}