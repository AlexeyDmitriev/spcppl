#include <cstddef>
#include <gtest/gtest.h>
#include <spcppl/Matrix.hpp>
#include <spcppl/make_constant.hpp>
#include "detectionIdiom.hpp"

MAKE_CONSTANT(N, std::size_t)
MAKE_CONSTANT(M, std::size_t)

using RectangularMatrix = FixedSizeMatrix<int, 2, 3>;
using SquareMatrix = FixedSizeMatrix<int, 2, 2>;
using RuntimeMatrix = Matrix<int, N, M>;

TEST(Matrix, CreationDefault) {
	RectangularMatrix matrix;
	ASSERT_EQ(matrix.rows(), static_cast<size_t>(2));
	ASSERT_EQ(matrix.columns(), static_cast<size_t>(3));
	for (std::size_t i = 0; i < matrix.rows(); ++i) {
		for (std::size_t j = 0; j < matrix.columns(); ++j) {
			ASSERT_EQ(matrix[i][j], 0) << "i: " << i << " j: " << j;
		}
	}
}

TEST(Matrix, CreationFromValue) {
	SquareMatrix matrix{5};
	ASSERT_EQ(matrix.rows(), static_cast<size_t>(2));
	ASSERT_EQ(matrix.columns(), static_cast<size_t>(2));
	for (std::size_t i = 0; i < matrix.rows(); ++i) {
		for (std::size_t j = 0; j < matrix.columns(); ++j) {
			ASSERT_EQ(matrix[i][j], 5) << "i: " << i << " j: " << j;
		}
	}
}

TEST(Matrix, CreationRuntime) {
	for (std::size_t i = 1; i < 5; ++i) {
		for (std::size_t j = 1; j < 5; ++j) {
			N::value = i;
			M::value = j;
			RuntimeMatrix matrix;
			ASSERT_EQ(matrix.rows(), static_cast<size_t>(i));
			ASSERT_EQ(matrix.columns(), static_cast<size_t>(j));
			ASSERT_EQ(matrix[0].size(), static_cast<size_t>(j));
		}
	}
}

TEST(Matrix, Add) {
	RectangularMatrix lhs;
	RectangularMatrix rhs;
	lhs[0][0] = 1;
	lhs[0][1] = 2;
	lhs[1][2] = 3;

	rhs[0][1] = 42;
	rhs[1][1] = 5;

	auto sum = lhs + rhs;
	static_assert(std::is_same<decltype(sum), RectangularMatrix>::value, "Wrong size");

	ASSERT_EQ(sum[0][0], 1);
	ASSERT_EQ(sum[0][1], 44);
	ASSERT_EQ(sum[0][2], 0);
	ASSERT_EQ(sum[1][0], 0);
	ASSERT_EQ(sum[1][1], 5);
	ASSERT_EQ(sum[1][2], 3);
}

TEST(Matrix, Identity) {
	auto id = identity<SquareMatrix>();
	ASSERT_EQ(id[0][0], 1);
	ASSERT_EQ(id[0][1], 0);
	ASSERT_EQ(id[1][0], 0);
	ASSERT_EQ(id[1][1], 1);

	SquareMatrix matrix;
	matrix[0] = {1, 2};
	matrix[1] = {5, 94};

	ASSERT_EQ(matrix * id, matrix);
	ASSERT_EQ(id * matrix, matrix);
}

TEST(Matrix, Transpose) {
	FixedSizeMatrix<int, 2, 3> matrix;
	matrix[0] = {1, 5, 6};
	matrix[1] = {2, 0, -1};

	auto transposed = matrix.transposed();
	static_assert(std::is_same<decltype(transposed), FixedSizeMatrix<int, 3, 2>>::value);

	ASSERT_EQ(transposed[0][0], 1);
	ASSERT_EQ(transposed[0][1], 2);
	ASSERT_EQ(transposed[1][0], 5);
	ASSERT_EQ(transposed[1][1], 0);
	ASSERT_EQ(transposed[2][0], 6);
	ASSERT_EQ(transposed[2][1], -1);
}

TEST(Matrix, Multiplication) {
	SquareMatrix square1;
	SquareMatrix square2;
	square1[0] = {5, 1};
	square1[1] = {8, 12};

	square2[0] = {9, 3};
	square2[1] = {5, 4};

	SquareMatrix product = square1 * square2;
	ASSERT_EQ(product[0][0], 50);
	ASSERT_EQ(product[0][1], 19);
	ASSERT_EQ(product[1][0], 132);
	ASSERT_EQ(product[1][1], 72);
}

template <typename LHS, typename RHS>
using multiply = decltype(std::declval<LHS>() * std::declval<RHS>());

template <typename LHS, typename RHS>
using multiply_assign = decltype(std::declval<LHS>() *= std::declval<RHS>());

TEST(Matrix, MultiplicationCompilation) {
	ASSERT_TRUE((is_detected_v<multiply, SquareMatrix, SquareMatrix>));
	ASSERT_FALSE((is_detected_v<multiply, RectangularMatrix, SquareMatrix>));
	ASSERT_TRUE((is_detected_v<multiply, SquareMatrix, RectangularMatrix>));
	ASSERT_FALSE((is_detected_v<multiply, RectangularMatrix, RectangularMatrix>));

	M::value = 2;
	N::value = 2;
	ASSERT_FALSE((is_detected_v<multiply, RuntimeMatrix, SquareMatrix>));
	ASSERT_FALSE((is_detected_v<multiply, RuntimeMatrix, RuntimeMatrix>));

	ASSERT_TRUE((is_detected_exact_v<SquareMatrix, multiply, RectangularMatrix, decltype(RectangularMatrix().transposed())>));
	ASSERT_TRUE((is_detected_exact_v<FixedSizeMatrix<int, 3, 3>, multiply, decltype(RectangularMatrix().transposed()), RectangularMatrix>));

	ASSERT_TRUE((is_detected_v<multiply_assign, SquareMatrix, SquareMatrix>));
	ASSERT_TRUE((is_detected_v<multiply_assign, RectangularMatrix, FixedSizeMatrix<int, 3, 3>>));
	ASSERT_FALSE((is_detected_v<multiply_assign, SquareMatrix, RectangularMatrix>));
	ASSERT_FALSE((is_detected_v<multiply_assign, RectangularMatrix, RectangularMatrix>));
	ASSERT_FALSE((is_detected_v<multiply_assign, RectangularMatrix, SquareMatrix>));
}
