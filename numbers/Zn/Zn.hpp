#pragma once

#include <iostream>
#include <assert.h>
#include "../extended_gcd.hpp"
#include "../../assert.hpp"
#include "../../identity.hpp"
#include "Normalizator.hpp"

template <long long mod, bool autoNormalize = true>
class Zn {
	static_assert(mod > 0, "Mod has to be positive integer");
public:

	/**
	* Not to be used
	*/
	Zn(): value(0) {
	}

	/**
	* Instead of ctor, to allow not to notmalize in ctor
	*/
	static Zn valueOf(long long value) {
		impl__Normalizator<true>::hard(value, mod);
		return Zn(value);
	}

	Zn& operator += (const Zn& rhs) {
		value += rhs.value;
		impl__Normalizator<autoNormalize>::softDown(value, mod);
		return *this;
	}

	Zn& operator += (long long rhs) {
		return *this += Zn::valueOf(rhs);
	}

	Zn& operator -= (const Zn& rhs) {
		value -= rhs.value;
		impl__Normalizator<autoNormalize>::softUp(value, mod);
		return *this;
	}

	Zn& operator -= (long long rhs) {
		return *this -= Zn::valueOf(rhs);
	}

	Zn& operator *= (const Zn& rhs) {
		value *= rhs.value;
		impl__Normalizator<autoNormalize>::hardDown(value, mod);
		return *this;
	}

	Zn& operator *= (long long rhs) {
		return *this *= Zn::valueOf(rhs);
	}

	/**
	* Changes internal state, but doesn't change logical state
	*/
	void normalize() const {
		long long& value = const_cast<long long&>(this->value);
		impl__Normalizator<!autoNormalize>::hard(value, mod);
	}

	Zn operator - () const {
		Zn result(mod - value);
		impl__Normalizator<autoNormalize>::softDown(result.value, mod);
		return result;
	}

	Zn& operator /= (const Zn& rhs) {
		return *this *= rhs.inversed();
	}

	Zn& operator /= (long long rhs) {
		return *this /= Zn::valueOf(rhs);
	}

	bool operator == (const Zn& rhs) const {
		normalize();
		rhs.normalize();
		return value == rhs.value;
	}

	Zn inversed() const {
		SPCPPL_ASSERT(value != 0);
		normalize();

		long long x, y;
		long long gcd = extended_gcd(value, mod, x, y);
		(void)gcd;
		SPCPPL_ASSERT(gcd == 1);

		impl__Normalizator<autoNormalize>::softUp(x, mod);
		return Zn(x);
	}
	template <long long m, bool aF>
	friend std::ostream& operator << (std::ostream&, const Zn<m, aF>& zn);
	template <long long m, bool aF>
	friend std::istream& operator >> (std::istream&, Zn<m, aF>& zn);

	long long longValue() const {
		return value;
	}
private:

	/**
	* No normalization performed
	*/
	explicit Zn(long long value): value(value) {
	}

	long long value;
};

template <long long m, bool a>
Zn<m, a> operator + (const Zn<m, a>& lhs, const Zn<m, a>& rhs) {
	Zn<m, a> copy = lhs;
	return copy += rhs;
}

template <long long m, bool a>
Zn<m, a> operator + (const Zn<m, a>& lhs, long long rhs) {
	Zn<m, a> copy = lhs;
	return copy += rhs;
}

template <long long m, bool a>
Zn<m, a> operator - (const Zn<m, a>& lhs, const Zn<m, a>& rhs) {
	Zn<m, a> copy = lhs;
	return copy -= rhs;
}

template <long long m, bool a>
Zn<m, a> operator - (const Zn<m, a>& lhs, long long rhs) {
	Zn<m, a> copy = lhs;
	return copy -= rhs;
}

template <long long m, bool a>
Zn<m, a> operator * (const Zn<m, a>& lhs, const Zn<m, a>& rhs) {
	Zn<m, a> copy = lhs;
	return copy *= rhs;
}

template <long long m, bool a>
Zn<m, a> operator * (const Zn<m, a>& lhs, long long rhs) {
	Zn<m, a> copy = lhs;
	return copy *= rhs;
}

template <long long m, bool a>
Zn<m, a> operator / (const Zn<m, a>& lhs, const Zn<m, a>& rhs) {
	Zn<m, a> copy = lhs;
	return copy /= rhs;
}

template <long long m, bool a>
Zn<m, a> operator / (const Zn<m, a>& lhs, long long rhs) {
	Zn<m, a> copy = lhs;
	return copy /= rhs;
}

template <long long m, bool a>
std::ostream& operator <<(std::ostream& stream, const Zn<m, a>& zn) {
	zn.normalize();
	return stream << zn.value;
}

template <long long m, bool a>
std::istream& operator >>(std::istream& stream, Zn<m, a>& zn) {
	stream >> zn.value;
	impl__Normalizator<a>::hard(zn.value, m);
	return stream;
}

template <long long m, bool a>
struct impl__IdentityHelper<Zn<m, a>> {
	static Zn<m, a> identity() {
		return Zn<m, a>::valueOf(1);
	}
};


