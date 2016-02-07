#pragma once

#include <cmath>
#include <tuple>
#include "../assert.hpp"
#include <cmath>

template <typename T, typename SquareT = T>
struct Point2D {
	T x, y;

	Point2D(): x(0), y(0) {
	}

	Point2D(T x, T y): x(x), y(y) {
	}

	SquareT squaredDist() const {
		return static_cast<SquareT>(x) * x + static_cast<SquareT>(y) * y;
	}

	auto dist() -> decltype(sqrt(squaredDist())) {
		return sqrt(squaredDist());
	}

	double angle() const {
		return atan2(y, x);
	}

	Point2D& operator-=(const Point2D& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Point2D& operator+=(const Point2D& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Point2D& operator*=(T rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Point2D& operator/=(T rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	T& operator[](size_t i) {
		if (i == 0) {
			return x;
		}
		if (i == 1) {
			return y;
		}
		SPCPPL_ASSERT(false);
	}

	const T& operator[](size_t i) const {
		if (i == 0) {
			return x;
		}
		if (i == 1) {
			return y;
		}
		SPCPPL_ASSERT(false);
	}

	template <typename U, typename V = U>
	Point2D<U, V> as() {
		return {U(x), U(y)};
	}
};

template <typename T, typename S>
Point2D<T, S> operator+(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) {
	return Point2D<T, S>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T, typename S>
Point2D<T, S> operator-(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) {
	return Point2D<T, S>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T, typename S>
Point2D<T, S> operator*(const Point2D<T, S>& lhs, T rhs) {
	return Point2D<T, S>(lhs.x * rhs, lhs.y * rhs);
}

template <typename T, typename S>
Point2D<T, S> operator*(T lhs, const Point2D<T, S>& rhs) {
	return Point2D<T, S>(lhs * rhs.x, lhs * rhs.y);
}

template <typename T, typename S>
Point2D<T, S> operator/(const Point2D<T, S>& lhs, T rhs) {
	return Point2D<T, S>(lhs.x / rhs, lhs.y / rhs);
}

template <typename T, typename S>
S operator*(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) {
	return static_cast<S>(lhs.x) * rhs.y - static_cast<S>(rhs.x) * lhs.y;
}

template <typename T, typename S>
S operator%(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) {
	return static_cast<S>(lhs.x) * rhs.x + static_cast<S>(lhs.y) * rhs.y;
}

template <typename T, typename S>
bool operator==(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename T, typename S>
bool operator!=(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) {
	return !(lhs == rhs);
}

struct LexicograficallyLess {
	template <typename T, typename S>
	bool operator()(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) const {
		return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
	};
};

template <typename T, typename S>
struct LessByAngle {
	explicit LessByAngle(const Point2D<T>& center): center(center) {
	}

	bool operator() (Point2D<T, S> lhs, Point2D<T, S> rhs) {
		lhs -= center;
		rhs -= center;
		if (upper(lhs) != upper(rhs)) {
			return upper(rhs);
		}
		return lhs * rhs > 0;
	}
private:
	bool upper(const Point2D<T>& point) {
		return point.y > 0 || (point.y == 0 && point.x > 0);
	}
	Point2D<T, S> center;
};

template <typename T, typename S>
double distance_to_segment(const Point2D<T, S>& point, const Point2D<T, S>& b, const Point2D<T, S>& c) {
	static_assert(std::is_floating_point<T>::value, "only floating point implemented");
	auto ba = b - point;
	auto ca = c - point;
	if ((ba - ca) % ba >= 0 && (ca - ba) % ca >= 0) {
		return fabs(ba * ca) / (ca - ba).dist();
	}
	return std::min(ba.dist(), ca.dist());
};

template <typename T, typename S>
double distance_to_line(const Point2D<T, S>& point, const Point2D<T, S>& b, const Point2D<T, S>& c) {
	static_assert(std::is_floating_point<T>::value, "only floating point implemented");
	auto ba = b - point;
	auto ca = c - point;
	return fabs(ba * ca) / (ca - ba).dist();
};
