#pragma once

#include <vector>
#include "assert.hpp"
#include "matrixMultiplication.hpp"
#include "identity.hpp"
#include "make_vector.hpp"

template <typename T, typename N, typename M>
class Matrix {
public:
	explicit Matrix(const T& value = T()): value(make_vector<T>(rows(), columns(), value)) {

	}

	std::size_t rows() const {
		return N::value;
	}

	std::size_t columns() const {
		return M::value;
	}

	std::vector<T>& operator[](std::size_t index) {
		SPCPPL_ASSERT(index < rows());
		return value[index];
	}

	const std::vector<T>& operator[](std::size_t index) const {
		SPCPPL_ASSERT(index < rows());
		return value[index];
	}

	Matrix& operator*=(const Matrix<T, M, M>& rhs) {
		return *this = *this * rhs;
	}

	Matrix& operator+=(const Matrix& rhs) {
		for (std::size_t i = 0; i < rows(); ++i) {
			for (std::size_t j = 0; j < columns(); ++j) {
				value[i][j] += rhs.value[i][j];
			}
		}
		return *this;
	}

	Matrix operator-() const {
		Matrix copy = *this;
		for (int i = 0; i < rows(); ++i) {
			for (int j = 0; j < columns(); ++j) {
				copy[i][j] = -copy[i][j];
			}
		}
		return copy;
	}

	Matrix operator-=(const Matrix& rhs) {
		return *this += -rhs;
	}

	Matrix<T, M, N> transposed() const {
		Matrix<T, M, N> res;
		for (std::size_t i = 0; i < rows(); ++i) {
			for (std::size_t j = 0; j < columns(); ++j) {
				res[j][i] = value[i][j];
			}
		}
		return res;
	}

private:
	std::vector<std::vector<T>> value;

	template <typename U, typename V, typename W>
	friend bool operator==(const Matrix<U, V, W>& lhs, const Matrix<U, V, W>& rhs);
};

template <typename T, typename N, typename M>
bool operator==(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
	return lhs.value == rhs.value;
}

template <typename T, typename N, typename M, typename K>
Matrix<T, N, K> operator*(const Matrix<T, N, M>& lhs, const Matrix<T, M, K>& rhs) {
	Matrix<T, N, K> res;
	impl::matrixMultiplication(lhs, rhs, res);
	return res;
}

template <typename T, typename N, typename M>
Matrix<T, N, M> operator+(Matrix<T, N, M> lhs, const Matrix<T, N, M>& rhs) {
	Matrix<T, N, M> copy = std::move(lhs);
	return copy += rhs;
}

template <typename T, typename N, typename M>
Matrix<T, N, M> operator-(Matrix<T, N, M> lhs, const Matrix<T, N, M>& rhs) {
	Matrix<T, N, M> copy = std::move(lhs);
	return copy -= rhs;
}

template <typename T, typename N>
struct IdentityHelper<Matrix<T, N, N>> {
	static Matrix<T, N, N> identity() {
		Matrix<T, N, N> res;
		for (std::size_t i = 0; i < N::value; ++i) {
			res[i][i] = ::identity<T>();
		}
		return res;
	}
};

template <typename T, std::size_t n, std::size_t m>
using FixedSizeMatrix = Matrix<T, std::integral_constant<std::size_t, n>, std::integral_constant<std::size_t, m>>;
