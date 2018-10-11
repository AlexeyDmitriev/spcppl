#pragma once

#include <cmath>
#include <spcppl/assert.hpp>

template <typename T, typename SquareT = T>
struct Point3D {
	T x, y, z;

	Point3D(): x(0), y(0), z(0) {
	}

	Point3D(T x, T y, T z): x(x), y(y), z(z) {
	}

	SquareT squaredDist() const {
		return static_cast<SquareT>(x) * x + static_cast<SquareT>(y) * y + static_cast<SquareT>(z) * z;
	}

	auto dist() const -> decltype(sqrt(this->squaredDist())) {
		return sqrt(squaredDist());
	}

	Point3D& operator-= (const Point3D& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Point3D& operator+= (const Point3D& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Point3D& operator*=(T rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	Point3D& operator/=(T rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	T& operator[](std::size_t i) {
		if (i == 0) {
			return x;
		}
		if (i == 1) {
			return y;
		}
		if (i == 2) {
			return z;
		}
		SPCPPL_ASSERT(false);
	}

	const T& operator[](std::size_t i) const {
		if (i == 0) {
			return x;
		}
		if (i == 1) {
			return y;
		}
		if (i == 2) {
			return z;
		}
		SPCPPL_ASSERT(false);
	}

	template <typename U, typename V = U>
	Point3D<U, V> as() {
		return {U(x), U(y), U(z)};
	}

	Point3D normalized() const {
		static_assert(std::is_floating_point<T>::value, "only implemented for floating point types");
		return *this / dist();
	}
};

template <typename T, typename S>
Point3D<T, S> operator+(Point3D<T, S> lhs, const Point3D<T, S>& rhs) {
	return lhs += rhs;
};

template <typename T, typename S>
Point3D<T, S> operator-(Point3D<T, S> lhs, const Point3D<T, S>& rhs) {
	return lhs -= rhs;
};

template <typename T, typename S>
Point3D<T, S> operator*(T lhs, Point3D<T, S> rhs) {
	return rhs *= lhs;
};

template <typename T, typename S>
Point3D<T, S> operator*(Point3D<T, S> lhs, T rhs) {
	return lhs *= rhs;
};

template <typename T, typename S>
Point3D<T, S> operator/(const Point3D<T, S>& lhs, T rhs) {
	return Point3D<T, S>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

template <typename S>
Point3D<S, S> operator*(const Point3D<S, S>& lhs, const Point3D<S, S>& rhs) {
	return Point3D<S, S>(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
	);
}

template <typename T, typename S>
S operator%(const Point3D<T, S>& lhs, const Point3D<T, S>& rhs) {
	return static_cast<S>(lhs.x) * rhs.x + static_cast<S>(lhs.y) * rhs.y + static_cast<S>(lhs.z) * rhs.z;
}

template <typename T, typename S>
bool operator==(const Point3D<T, S>& lhs, const Point3D<T, S>& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <typename T, typename S>
bool operator!=(const Point3D<T, S>& lhs, const Point3D<T, S>& rhs) {
	return !(lhs == rhs);
}
