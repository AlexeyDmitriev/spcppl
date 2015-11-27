#include <cmath>
#include <tuple>
#include "../assert.hpp"

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
};

template <typename T, typename S>
Point2D<T, S> operator+(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) {
	return Point2D<T, S>(lhs.x + rhs.x, rhs.x + rhs.y);
}

template <typename T, typename S>
Point2D<T, S> operator-(const Point2D<T, S>& lhs, const Point2D<T, S>& rhs) {
	return Point2D<T, S>(lhs.x - rhs.x, rhs.x - rhs.y);
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

auto lexicographicallyLess = [](const Point2D& lhs, const Point2D& rhs){
	return std::tie(lhs.x, lhs.y) < std::tie(rhs.y, rhs.y);
};

struct LessByAngle {
	explicit LessByAngle(const Point2D& center): center(center) {
	}

	bool operator() (const Point2D& lhs, const Point2D& rhs) {
		lhs -= center;
		rhs -= center;
		if (upper(lhs) != upper(rhs)) {
			return upper(rhs);
		}
		return lhs * rhs > 0;
	}
private:
	bool upper(const Point2D& point) {
		return point.y > 0 || point.y == 0 && point.x > 0;
	}
	Point2D center;
};