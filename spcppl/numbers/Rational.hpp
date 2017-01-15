#pragma once

#include <iostream>
#include <spcppl/identity.hpp>
#include <spcppl/assert.hpp>
#include "gcd.hpp"

template <typename T>
class Rational {
public:
	Rational(): numerator(0), denominator(1) {
	}

	Rational(T numerator): numerator(numerator), denominator(1) {
	}

	Rational(T numerator, T denominator): numerator(numerator), denominator(denominator) {
		SPCPPL_ASSERT(denominator != 0);
		normalize();
	}

	Rational& operator+=(const Rational& rhs) {
		return *this = *this + rhs;
	}

	Rational& operator-=(const Rational& rhs) {
		return *this = *this - rhs;
	}

	Rational& operator*=(const Rational& rhs) {
		numerator *= rhs.numerator;
		denominator *= rhs.denominator;
		normalize();
		return *this;
	}

	Rational operator-() const {
		return Rational(-numerator, denominator);
	}

	Rational& operator/=(const Rational& rhs) {
		SPCPPL_ASSERT(rhs.numerator != 0);
		numerator *= rhs.denominator;
		denominator *= rhs.numerator;
		normalize();
		return *this;
	}

	bool operator==(const Rational& rhs) const {
		return numerator == rhs.numerator && denominator == rhs.denominator;
	}

	const T& getNumerator() const {
		return numerator;
	}

	const T& getDenominator() const {
		return denominator;
	}

private:
	void normalize() {
		T g = gcd(numerator, denominator);
		numerator /= g;
		denominator /= g;

		if (denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
	}

	T numerator, denominator;

	template <typename U>
	friend Rational<U> operator+(const Rational<U>& lhs, const Rational<U>& rhs);
};


template <typename T>
Rational<T> operator+(const Rational<T>& lhs, const Rational<T>& rhs) {
	T g = gcd(lhs.denominator, rhs.denominator);
	return Rational<T>(
			lhs.numerator * (rhs.denominator / g) + rhs.numerator * (lhs.denominator / g),
			lhs.denominator / g * rhs.denominator
	);
}

template <typename T>
Rational<T> operator-(const Rational<T>& lhs, const Rational<T>& rhs) {
	return lhs + (-rhs);
}

template <typename T>
Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {
	Rational<T> copy = lhs;
	return copy *= rhs;
}

template <typename T>
Rational<T> operator/(const Rational<T>& lhs, const Rational<T>& rhs) {
	Rational<T> copy = lhs;
	return copy /= rhs;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Rational<T>& rational) {
	return stream << rational.getNumerator() << '/' << rational.getDenominator();
}

template <typename T>
struct IdentityHelper<Rational<T>> {
	static Rational<T> identity() {
		return Rational<T>(1);
	}
};

template <typename T>
bool operator==(const Rational<T>& lhs, const Rational<T>& rhs) {
	return lhs.getNumerator() * rhs.getDenominator() == lhs.getDenominator() * rhs.getNumerator();
}

template <typename T>
bool operator!=(const Rational<T>& lhs, const Rational<T>& rhs) {
	return !(lhs == rhs);
}

template <typename T>
bool operator<(const Rational<T>& lhs, const Rational<T>& rhs) {
	return lhs.getNumerator() * rhs.getDenominator() < lhs.getDenominator() * rhs.getNumerator();
}

template <typename T>
bool operator>(const Rational<T>& lhs, const Rational<T>& rhs) {
	return rhs < lhs;
}

template <typename T>
bool operator<=(const Rational<T>& lhs, const Rational<T>& rhs) {
	return !(lhs > rhs);
}

template <typename T>
bool operator>=(const Rational<T>& lhs, const Rational<T>& rhs) {
	return !(lhs < rhs);
}

