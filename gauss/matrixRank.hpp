#pragma once

#include <cstddef>
#include "../Matrix.hpp"
#include "reduceToRowEchelonForm.hpp"

template <typename T>
std::size_t matrixRank(Matrix<T> matrix) {
	return reduceToRowEchelonForm(matrix);
}