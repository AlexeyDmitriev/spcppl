#pragma once

#include <iostream>
#include "gcd.hpp"

template <typename T>
class Rational {
public:
	Rational():numerator(0), denominator(1) {
	}
	Rational(T numerator): numerator(numerator), denominator(1) {
	}
	Rational(T numerator, T denominator): numerator(numerator), denominator(denominator) {
		normalize();
	}

	Rational& operator += (const Rational& rhs) {
		return *this = *this + rhs;
	}

	Rational& operator -= (const Rational& rhs) {
		return *this = *this - rhs;
	}

	Rational& operator *= (const Rational& rhs) {
		numerator *= rhs.numerator;
		denominator *= rhs.denominator;
		normalize();
		return *this;
	}

	Rational operator - () const {
		return Rational(-numerator, denominator);
	}

	Rational& operator /= (const Rational& rhs) {
		numerator *= rhs.denominator;
		denominator *= rhs.numerator;
		normalize();
		return *this;
	}

	bool operator == (const Rational& rhs) const {
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

		if(denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
	}
	T numerator, denominator;
};


//TODO: avoid overflow by dividing early
template <typename T>
Rational<T> operator + (const Rational<T>& lhs, const Rational<T>& rhs) {
	return Rational<T>(
			lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator,
			lhs.denominator * rhs.denominator
	);
}

template <typename T>
Rational<T> operator - (const Rational<T>& lhs, const Rational<T>& rhs) {
	return lhs + (-rhs);
}

template <typename T>
Rational<T> operator * (const Rational<T>& lhs, const Rational<T>& rhs) {
	Rational<T> copy = lhs;
	return copy *= rhs;
}

template <typename T>
Rational<T> operator / (const Rational<T>& lhs, const Rational<T>& rhs) {
	Rational<T> copy = lhs;
	return copy /= rhs;
}

template <typename T>
std::ostream& operator <<(std::ostream& stream, const Rational<T>& rational) {
	return stream << rational.getNumerator() << '/' << rational.getDenominator();
}
template <typename T>
struct impl__IdentityHelper<Rational<T>> {
	static Rational<T> identity() {
		return Rational<T>(1);
	}
};

