#pragma once

#include "../Matrix.hpp"
#include "reduceToRowEchelonForm.hpp"

template <typename T, typename N>
T impl__determinant(Matrix<T, N, N> matrix, const T& one) {
	reduceToRowEchelonForm(matrix);

	T result = one;
	for (std::size_t i: range(matrix.rows())) {
		result *= matrix[i][i];
	}
	return result;
}

template <typename T, typename N>
T determinant(Matrix<T, N, N> matrix) {
	return impl__determinant(std::move(matrix), identity<T>());
}

template <typename T, typename N>
T determinant(Matrix<T, N, N>& matrix, const T& sample) {
	return impl__determinant(std::move(matrix), identity<T>(sample));
}
