#pragma once

#include <iostream>
#include <assert.h>
#include "../assert.hpp"
#include "../identity.hpp"
#include "extendedGcd.hpp"

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
	* Instead of ctor, to allow not to normalize in ctor
	*/
	static Zn valueOf(int value) {
		return Zn(value % mod);
	}

	static Zn valueOf(long long value) {
		return Zn(static_cast<int>(value) % mod);
	}

	static Zn rawValueOf(int value) {
		SPCPPL_ASSERT(value >= 0 && value < mod);
		return Zn(value);
	}

	Zn& operator=(int rhs) {
		return *this = Zn::valueOf(rhs);
	}

	Zn& operator=(long long rhs) {
		return *this = Zn::valueOf(rhs);
	}

	Zn& operator+=(const Zn& rhs) {
		value += rhs.value;
		if (value >= mod) {
			value -= mod;
		}
		return *this;
	}

	Zn& operator+=(int rhs) {
		return *this += Zn::valueOf(rhs);
	}

	Zn& operator+=(long long rhs) {
		return *this += Zn::valueOf(rhs);
	}

	Zn& operator-=(const Zn& rhs) {
		value -= rhs.value;
		if (value < 0) {
			value += mod;
		}
		return *this;
	}

	Zn& operator-=(int rhs) {
		return *this -= Zn::valueOf(rhs);
	}

	Zn& operator-=(long long rhs) {
		return *this -= Zn::valueOf(rhs);
	}

	Zn& operator*=(const Zn& rhs) {
		long long result = static_cast<long long>(value) * static_cast<long long>(rhs.value);
		value = static_cast<int>(result % mod);
		return *this;
	}

	Zn& operator*=(int rhs) {
		return *this *= Zn::valueOf(rhs);
	}

	Zn& operator*=(long long rhs) {
		return *this *= Zn::valueOf(rhs);
	}

	Zn operator-() const {
		if (value == 0) {
			return *this;
		}
		else {
			return Zn(mod - value);
		}
	}

	Zn& operator/=(const Zn& rhs) {
		return *this *= rhs.inversed();
	}

	Zn& operator/=(int rhs) {
		return *this /= Zn::valueOf(rhs);
	}

	Zn& operator/=(long long rhs) {
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

		if (x < 0) {
			x += mod;
		}
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
bool operator==(const Zn<m>& lhs, long long rhs) {
	return lhs == Zn::valueOf(rhs);
}

template <int m>
bool operator==(long long lhs, Zn<m>& rhs) {
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
bool operator!=(const Zn<m>& lhs, long long rhs) {
	return !(lhs == rhs);
}

template <int m>
bool operator!=(const Zn<m>& lhs, long long rhs) {
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
Zn<m> operator+(const Zn<m>& lhs, long long rhs) {
	Zn<m> copy = lhs;
	return copy += rhs;
}

template <int m>
Zn<m> operator+(long long lhs, const Zn<m>& rhs) {
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
Zn<m> operator-(const Zn<m>& lhs, long long rhs) {
	Zn<m> copy = lhs;
	return copy -= rhs;
}

template <int m>
Zn<m> operator-(long lhs, const Zn<m>& rhs) {
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
Zn<m> operator*(const Zn<m>& lhs, long long rhs) {
	Zn<m> copy = lhs;
	return copy *= rhs;
}

template <int m>
Zn<m> operator*(long long lhs, const Zn<m>& rhs) {
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
Zn<m> operator/(const Zn<m>& lhs, long long rhs) {
	Zn<m> copy = lhs;
	return copy /= rhs;
}

template <int m>
Zn<m> operator/(long long lhs, const Zn<m>& rhs) {
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
	zn.value = static_cast<int>(value % m);
	return stream;
}

template <int m>
struct impl__IdentityHelper<Zn<m>> {
	static Zn<m> identity() {
		return Zn<m>::valueOf(1);
	}
};
