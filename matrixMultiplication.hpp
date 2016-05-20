#pragma once

#include <cstddef>

namespace impl {

template <typename T, typename U, typename V>
void matrixMultiplication(const T& lhs, const U& rhs, V& res) {
	const auto& a = lhs;
	auto b = rhs.transposed();
	for (std::size_t i = 0; i < lhs.rows(); ++i) {
		for (std::size_t j = 0; j < rhs.columns(); ++j) {
			for (std::size_t k = 0; k < rhs.rows(); ++k) {
				res[i][j] += a[i][k] * b[j][k];
			}
		}
	}
}

} // namespace impl
