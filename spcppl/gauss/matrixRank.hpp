#pragma once

#include <cstddef>
#include <spcppl/Matrix.hpp>
#include "reduceToRowEchelonForm.hpp"

template <typename T, typename N, typename M>
std::size_t matrixRank(Matrix<T, N, M> matrix) {
	return reduceToRowEchelonForm(matrix);
}
