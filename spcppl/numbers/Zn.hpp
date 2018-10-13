#pragma once

#include <iostream>
#include <assert.h>
#include <type_traits>
#include <spcppl/typeTraits/enable_if_t.hpp>
#include <spcppl/typeTraits/IsSaneInteger.hpp>
#include <spcppl/assert.hpp>
#include <spcppl/identity.hpp>
#include "extendedGcd.hpp"

template <typename T>
class Zn {
public:
	Zn(): value(0) {
	}

	/**
	* Instead of ctor, to allow not to normalize in ctor
	*/
	template <typename U, typename E = enable_if_t<IsSaneInteger<U>>>
	static Zn valueOf(U value) {
		int x = static_cast<int>(value % mod());
		if (x < 0) {
			x += mod();
		}
		return Zn(x);
	}

	static Zn rawValueOf(int value) {
		SPCPPL_ASSERT(value >= 0 && value < mod());
		return Zn(value);
	}

	template <typename U, typename E = enable_if_t<IsSaneInteger<U>>>
	Zn& operator=(U rhs) {
		return *this = Zn::valueOf(rhs);
	}


	Zn& operator+=(const Zn& rhs) {
		value += rhs.value;
		if (value >= mod()) {
			value -= mod();
		}
		return *this;
	}

	template <typename U, typename E = enable_if_t<IsSaneInteger<U>>>
	Zn& operator+=(U rhs) {
		return *this += Zn::valueOf(rhs);
	}

	Zn& operator-=(const Zn& rhs) {
		value -= rhs.value;
		if (value < 0) {
			value += mod();
		}
		return *this;
	}

	template <typename U, typename E = enable_if_t<IsSaneInteger<U>>>
	Zn& operator-=(U rhs) {
		return *this -= Zn::valueOf(rhs);
	}

	Zn& operator*=(const Zn& rhs) {
		long long result = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
		value = static_cast<int>(result % mod());
		return *this;
	}

	template <typename U, typename E = enable_if_t<IsSaneInteger<U>>>
	Zn& operator*=(U rhs) {
		return *this *= Zn::valueOf(rhs);
	}

	Zn operator-() const {
		if (value == 0) {
			return *this;
		}
		else {
			return Zn(mod() - value);
		}
	}

	Zn& operator/=(const Zn& rhs) {
		return *this *= rhs.inversed();
	}

	template <typename U, typename E = enable_if_t<IsSaneInteger<U>>>
	Zn& operator/=(U rhs) {
		return *this /= Zn::valueOf(rhs);
	}

	Zn inversed() const {
		SPCPPL_ASSERT(value != 0);

		int x, y;
		int gcd = extendedGcd(value, mod(), x, y);
		(void) gcd;
		SPCPPL_ASSERT(gcd == 1);

		if (x < 0) {
			x += mod();
		}
		return Zn(x);
	}

	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const Zn<U>& zn);

	template <typename U>
	friend std::istream& operator>>(std::istream&, Zn<U>& zn);

	template <typename U>
	friend bool operator==(const Zn<U>& lhs, const Zn<U>& rhs);

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

	constexpr static int mod() {
		return T::value;
	}

	template <int N = T::value>
	static constexpr bool correct_or_runtime(int) {
		return N > 0 && N <= (1 << 30);
	}
	static constexpr bool correct_or_runtime(...) {
		return true;
	}
	static_assert(
			std::is_same<typename std::decay<decltype(T::value)>::type, int>::value,
			"T::value must be int"
	);
	static_assert(correct_or_runtime(0), "Mod has to be positive integer up to 1 << 30");
};

template <typename T>
bool operator==(const Zn<T>& lhs, const Zn<T>& rhs) {
	return lhs.value == rhs.value;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
bool operator==(const Zn<T>& lhs, U rhs) {
	return lhs == Zn<T>::valueOf(rhs);
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
bool operator==(U lhs, const Zn<T>& rhs) {
	return rhs == lhs;
}

template <typename T>
bool operator!=(const Zn<T>& lhs, const Zn<T>& rhs) {
	return !(lhs == rhs);
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
bool operator!=(const Zn<T>& lhs, U rhs) {
	return !(lhs == rhs);
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
bool operator!=(U lhs, const Zn<T>& rhs) {
	return !(lhs == rhs);
}

template <typename T>
Zn<T> operator+(const Zn<T>& lhs, const Zn<T>& rhs) {
	Zn<T> copy = lhs;
	return copy += rhs;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
Zn<T> operator+(const Zn<T>& lhs, U rhs) {
	Zn<T> copy = lhs;
	return copy += rhs;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
Zn<T> operator+(U lhs, const Zn<T>& rhs) {
	return rhs + lhs;
}

template <typename T>
Zn<T> operator-(const Zn<T>& lhs, const Zn<T>& rhs) {
	Zn<T> copy = lhs;
	return copy -= rhs;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
Zn<T> operator-(const Zn<T>& lhs, U rhs) {
	Zn<T> copy = lhs;
	return copy -= rhs;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
Zn<T> operator-(U lhs, const Zn<T>& rhs) {
	return Zn<T>::valueOf(lhs) - rhs;
}

template <typename T>
Zn<T> operator*(const Zn<T>& lhs, const Zn<T>& rhs) {
	Zn<T> copy = lhs;
	return copy *= rhs;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
Zn<T> operator*(const Zn<T>& lhs, U rhs) {
	Zn<T> copy = lhs;
	return copy *= rhs;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
Zn<T> operator*(U lhs, const Zn<T>& rhs) {
	return rhs * lhs;
}

template <typename T>
Zn<T> operator/(const Zn<T>& lhs, const Zn<T>& rhs) {
	Zn<T> copy = lhs;
	return copy /= rhs;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
Zn<T> operator/(const Zn<T>& lhs, U rhs) {
	Zn<T> copy = lhs;
	return copy /= rhs;
}

template <typename T, typename U, typename E = enable_if_t<IsSaneInteger<U>>>
Zn<T> operator/(U lhs, const Zn<T>& rhs) {
	return Zn<T>::valueOf(lhs) / rhs;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Zn<T>& zn) {
	return stream << zn.value;
}

template <typename T>
std::istream& operator>>(std::istream& stream, Zn<T>& zn) {
	int64_t value;
	stream >> value;
	zn.value = static_cast<int>(value % T::value);
	return stream;
}

template <typename T>
struct IdentityHelper<Zn<T>> {
	static Zn<T> identity() {
		return Zn<T>::valueOf(1);
	}
};

template <int m>
using ZnConst = Zn<std::integral_constant<int, m>>;

using Zn7 = ZnConst<1000000007>;
