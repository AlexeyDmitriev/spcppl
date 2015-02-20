#pragma once

#include <iostream>
#include "extended_gcd.hpp"
#include "assert.hpp"


//FIXME: remove {} when CPP-1825 fixed.
template <bool normalize>
struct impl__Normalizator {

};

template <>
struct impl__Normalizator<true> {
	static void softUp(long long& value, long long mod) {
		if (value < 0) {
			value += mod;
		}
	}

	static void softDown(long long& value, long long mod) {
		if (value >= mod) {
			value -= mod;
		}
	}

	static void hardDown(long long& value, long long mod) {
		value %= mod;
	}

	static void hard(long long& value, long long mod) {
		value %= mod;
		softUp(value, mod);
	}
};

template <>
struct impl__Normalizator<false> {
	static void softUp(long long& value, long long mod) {
	}

	static void softDown(long long& value, long long mod) {
	}

	static void hardDown(long long& value, long long mod) {
	}

	static void hard(long long& value, long long mod) {
	}
};

template <long long mod, bool autoNormalize = true>
class Zn {
public:
	static_assert(mod > 0, "modulo should be positive");
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

	Zn& operator -= (const Zn& rhs) {
		value -= rhs.value;
		impl__Normalizator<autoNormalize>::softUp(value, mod);
		return *this;
	}

	Zn& operator *= (const Zn& rhs) {
		value *= rhs.value;
		impl__Normalizator<autoNormalize>::hardDown(value, mod);
		return *this;
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
		SPCPPL_ASSERT(gcd == 1);

		impl__Normalizator<autoNormalize>::softUp(x, mod);
		return Zn(x);
	}
	template <long long modF, bool aF>
	friend std::ostream& operator << (std::ostream&, const Zn<modF, aF>& zn);
	template <long long modF, bool aF>
	friend std::istream& operator >> (std::istream&, Zn<modF, aF>& zn);
private:

	/**
	* No normalization performed
	*/
	explicit Zn(long long value): value(value) {
	}

	long long value;
};

template <long long mod, bool a>
Zn<mod, a> operator + (const Zn<mod, a>& lhs, const Zn<mod, a>& rhs) {
	Zn<mod, a> copy = lhs;
	return copy += rhs;
}

template <long long mod, bool a>
Zn<mod, a> operator - (const Zn<mod, a>& lhs, const Zn<mod, a>& rhs) {
	Zn<mod, a> copy = lhs;
	return copy -= rhs;
}

template <long long mod, bool a>
Zn<mod, a> operator * (const Zn<mod, a>& lhs, const Zn<mod, a>& rhs) {
	Zn<mod, a> copy = lhs;
	return copy *= rhs;
}

template <long long mod, bool a>
Zn<mod, a> operator / (const Zn<mod, a>& lhs, const Zn<mod, a>& rhs) {
	Zn<mod, a> copy = lhs;
	return copy /= rhs;
}

template <long long mod, bool a>
std::ostream& operator <<(std::ostream& stream, const Zn<mod, a>& zn) {
	zn.normalize();
	return stream << zn.value;
}

template <long long mod, bool a>
std::istream& operator >>(std::istream& stream, Zn<mod, a>& zn) {
	stream >> zn.value;
	impl__Normalizator<a>::hard(zn.value, mod);
	return stream;
}

template <long long mod, bool a>
struct impl__IdentityHelper<Zn<mod, a>> {
	static Zn<mod, a> identity() {
		return Zn<mod, a>::valueOf(1);
	}
};

