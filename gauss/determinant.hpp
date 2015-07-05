#pragma once

#include "../Matrix.hpp"
#include "reduceToRowEchelonForm.hpp"

template <typename T>
T impl__determinant(Matrix<T> matrix, const T& one) {
	SPCPPL_ASSERT(matrix.rows() == matrix.columns());
	reduceToRowEchelonForm(matrix);

	T result = one;
	for (std::size_t i: range(matrix.rows())) {
		result *= matrix[i][i];
	}
	return result;
}

template <typename T>
T determinant(Matrix<T> matrix) {
	return impl__determinant(std::move(matrix), identity<T>());
}

template <typename T>
T determinant(Matrix<T>& matrix, const T& sample) {
	return impl__determinant(std::move(matrix), identity<T>(sample));
}