#pragma once

#include <iostream>
#include <assert.h>
#include "../assert.hpp"
#include "../identity.hpp"
#include "extendedGcd.hpp"

struct impl__Normalizator {
	static void softUp(int& value, int mod) {
		if (value < 0) {
			value += mod;
		}
	}

	static void softDown(int& value, int mod) {
		if (value >= mod) {
			value -= mod;
		}
	}

	template <typename T>
	static void hardDown(T& value, int mod) {
		value %= mod;
	}

	template <typename T>
	static void hard(T& value, int mod) {
		value %= mod;
		softUp(value, mod);
	}
};

template <int mod>
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
	static Zn valueOf(int value) {
		impl__Normalizator::hard(value, mod);
		return Zn(value);
	}
	static Zn valueOf(long long value) {
		impl__Normalizator::hard(value, mod);
		return Zn(static_cast<int>(value));
	}

	Zn& operator+=(const Zn& rhs) {
		value += rhs.value;
		impl__Normalizator::softDown(value, mod);
		return *this;
	}

	Zn& operator+=(int rhs) {
		return *this += Zn::valueOf(rhs);
	}

	Zn& operator-=(const Zn& rhs) {
		value -= rhs.value;
		impl__Normalizator::softUp(value, mod);
		return *this;
	}

	Zn& operator-=(int rhs) {
		return *this -= Zn::valueOf(rhs);
	}

	Zn& operator*=(const Zn& rhs) {
		long long result = value;
		result *= rhs.value;
		impl__Normalizator::hardDown(result, mod);
		value = static_cast<int>(result);
		return *this;
	}

	Zn& operator*=(int rhs) {
		return *this *= Zn::valueOf(rhs);
	}

	Zn operator-() const {
		Zn result(mod - value);
		impl__Normalizator::softDown(result.value, mod);
		return result;
	}

	Zn& operator/=(const Zn& rhs) {
		return *this *= rhs.inversed();
	}

	Zn& operator/=(int rhs) {
		return *this /= Zn::valueOf(rhs);
	}

	bool operator==(const Zn& rhs) const {
		return value == rhs.value;
	}

	Zn inversed() const {
		SPCPPL_ASSERT(value != 0);

		int x, y;
		int gcd = extendedGcd(value, mod, x, y);
		(void) gcd;
		SPCPPL_ASSERT(gcd == 1);

		impl__Normalizator::softUp(x, mod);
		return Zn(x);
	}

	template <int m>
	friend std::ostream& operator<<(std::ostream&, const Zn<m>& zn);

	template <int m>
	friend std::istream& operator>>(std::istream&, Zn<m>& zn);

	int intValue() const {
		return value;
	}

private:
	/**
	* No normalization performed
	*/
	explicit Zn(int value): value(value) {
	}

	int value;
};

template <int m>
bool operator==(const Zn<m>& lhs, int rhs) {
	return lhs == Zn<m>::valueOf(rhs);
}

template <int m>
bool operator==(int lhs, const Zn<m>& rhs) {
	return rhs == lhs;
}

template <int m>
bool operator!=(const Zn<m>& lhs, const Zn<m>& rhs) {
	return !(lhs == rhs);
}

template <int m>
bool operator!=(const Zn<m>& lhs, int rhs) {
	return !(lhs == rhs);
}

template <int m>
bool operator!=(int lhs, const Zn<m>& rhs) {
	return !(lhs == rhs);
}

template <int m>
Zn<m> operator+(const Zn<m>& lhs, const Zn<m>& rhs) {
	Zn<m> copy = lhs;
	return copy += rhs;
}

template <int m>
Zn<m> operator+(const Zn<m>& lhs, int rhs) {
	Zn<m> copy = lhs;
	return copy += rhs;
}

template <int m>
Zn<m> operator+(int lhs, const Zn<m>& rhs) {
	return rhs + lhs;
}

template <int m>
Zn<m> operator-(const Zn<m>& lhs, const Zn<m>& rhs) {
	Zn<m> copy = lhs;
	return copy -= rhs;
}

template <int m>
Zn<m> operator-(const Zn<m>& lhs, int rhs) {
	Zn<m> copy = lhs;
	return copy -= rhs;
}

template <int m>
Zn<m> operator-(int lhs, const Zn<m>& rhs) {
	return Zn<m>::valueOf(lhs) - rhs;
}

template <int m>
Zn<m> operator*(const Zn<m>& lhs, const Zn<m>& rhs) {
	Zn<m> copy = lhs;
	return copy *= rhs;
}

template <int m>
Zn<m> operator*(const Zn<m>& lhs, int rhs) {
	Zn<m> copy = lhs;
	return copy *= rhs;
}

template <int m>
Zn<m> operator*(int lhs, const Zn<m>& rhs) {
	return rhs * lhs;
}

template <int m>
Zn<m> operator/(const Zn<m>& lhs, const Zn<m>& rhs) {
	Zn<m> copy = lhs;
	return copy /= rhs;
}

template <int m>
Zn<m> operator/(const Zn<m>& lhs, int rhs) {
	Zn<m> copy = lhs;
	return copy /= rhs;
}

template <int m>
Zn<m> operator/(int lhs, const Zn<m>& rhs) {
	return Zn<m>::valueOf(lhs) / rhs;
}

template <int m>
std::ostream& operator<<(std::ostream& stream, const Zn<m>& zn) {
	return stream << zn.value;
}

template <int m>
std::istream& operator>>(std::istream& stream, Zn<m>& zn) {
	long long value;
	stream >> value;
	impl__Normalizator::hard(zn.value, m);
	zn.value = static_cast<int>(value);
	return stream;
}

template <int m>
struct impl__IdentityHelper<Zn<m>> {
	static Zn<m> identity() {
		return Zn<m>::valueOf(1);
	}
};


