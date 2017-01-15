#pragma once

#include <spcppl/Matrix.hpp>
#include "reduceToRowEchelonForm.hpp"

template <typename T, typename N>
T determinant(Matrix<T, N, N> matrix) {
	reduceToRowEchelonForm(matrix);

	T result = identity<T>();
	for (std::size_t i: range(matrix.rows())) {
		result *= matrix[i][i];
	}
	return result;
}
