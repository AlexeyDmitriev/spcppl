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

template <bool autoNormalize = true>
class Zn {
public:

	explicit Zn(long long mod): mod(mod), value(0) {

	}

	/**
	* Instead of ctor, to allow not to notmalize in ctor
	*/
	static Zn valueOf(long long mod, long long value) {
		impl__Normalizator<true>::hard(value, mod);
		return Zn(mod, value);
	}


	Zn& operator += (const Zn& rhs) {
		SPCPPL_ASSERT(mod == rhs.mod);
		value += rhs.value;
		impl__Normalizator<autoNormalize>::softDown(value, mod);
		return *this;
	}

	Zn& operator -= (const Zn& rhs) {
		SPCPPL_ASSERT(mod == rhs.mod);
		value -= rhs.value;
		impl__Normalizator<autoNormalize>::softUp(value, mod);
		return *this;
	}

	Zn& operator *= (const Zn& rhs) {
		SPCPPL_ASSERT(mod == rhs.mod);
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
		SPCPPL_ASSERT(mod == rhs.mod);
		Zn result(mod, mod - value);
		impl__Normalizator<autoNormalize>::softDown(result.value, mod);
		return result;
	}

	Zn& operator /= (const Zn& rhs) {
		return *this *= rhs.inversed();
	}

	bool operator == (const Zn& rhs) const {
		SPCPPL_ASSERT(mod == rhs.mod);
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
		return Zn(mod, x);
	}
	template <bool aF>
	friend std::ostream& operator << (std::ostream&, const Zn<aF>& zn);
	template <bool aF>
	friend std::istream& operator >> (std::istream&, Zn<aF>& zn);

	const long long mod;
private:

	/**
	* No normalization performed
	*/
	Zn(long long mod, long long value): mod(mod), value(value) {
	}

	long long value;
};

template <bool a>
Zn<a> operator + (const Zn<a>& lhs, const Zn<a>& rhs) {
	Zn<a> copy = lhs;
	return copy += rhs;
}

template <bool a>
Zn<a> operator - (const Zn<a>& lhs, const Zn<a>& rhs) {
	Zn<a> copy = lhs;
	return copy -= rhs;
}

template <bool a>
Zn<a> operator * (const Zn<a>& lhs, const Zn<a>& rhs) {
	Zn<a> copy = lhs;
	return copy *= rhs;
}

template <bool a>
Zn<a> operator / (const Zn<a>& lhs, const Zn<a>& rhs) {
	Zn<a> copy = lhs;
	return copy /= rhs;
}

template <bool a>
std::ostream& operator <<(std::ostream& stream, const Zn<a>& zn) {
	zn.normalize();
	return stream << zn.value;
}

template <bool a>
std::istream& operator >>(std::istream& stream, Zn<a>& zn) {
	stream >> zn.value;
	impl__Normalizator<a>::hard(zn.value, zn.mod);
	return stream;
}

template <bool a>
struct impl__SampleIdentityHelper<Zn<a>> {
	static Zn<a> identity(Zn<a>& sample) {
		return Zn<a>::valueOf(sample.mod, 1);
	}
};

