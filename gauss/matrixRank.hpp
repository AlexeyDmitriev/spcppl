#pragma once

#include <cstddef>
#include <iostream>
#include "../Matrix.hpp"
#include "../ranges/fors.hpp"

template <typename T>
std::size_t matrixRank(Matrix<T> matrix) {
	std::size_t rank = 0;

	for (std::size_t column: range(matrix.columns())) {
		bool found = false;
		for (std::size_t row: range(rank, matrix.rows())) {
			if (matrix[row][column] != 0) {
				using std::swap;
				found = true;
				swap(matrix[row], matrix[rank]);
				break;
			}
		}
		if (!found) {
			continue;
		}

		for (std::size_t r: range(rank + 1, matrix.rows())) {
			T multiplier = matrix[r][column] / matrix[rank][column];
			for (std::size_t c: range(column, matrix.columns())) {
				matrix[r][c] -= multiplier * matrix[rank][c];
			}
			SPCPPL_ASSERT(matrix[r][column] == 0);
		}
		++rank;
	}
	return rank;
}