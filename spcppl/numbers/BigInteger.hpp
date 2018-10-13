#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <spcppl/assert.hpp>
#include <spcppl/numbers/division.hpp>
#include <spcppl/ranges/Range.hpp>
#include <spcppl/ranges/wrappers.hpp>
#include <spcppl/typeTraits/IsSaneInteger.hpp>
#include <spcppl/typeTraits/enable_if_t.hpp>
#include <iostream>
#include <iomanip>

namespace detail {
bool compare_less(const std::vector<int32_t>& lhs, const std::vector<int32_t>& rhs) {
	if (lhs.size() != rhs.size()) {
		return lhs.size() < rhs.size();
	} else {
		return std::lexicographical_compare(lhs.rbegin(), lhs.rend(), rhs.rbegin(), rhs.rend());
	}
}
}  // namespace detail

class BigInteger {
public:
	BigInteger(): isNegative(false) {

	}

	// @todo: allow string-like types
	explicit BigInteger(const std::string& str) {
		SPCPPL_ASSERT(!str.empty());
		std::size_t start = 0;
		if (str[0] == '-') {
			isNegative = true;
			start = 1;
		} else {
			isNegative = false;
			if (str[0] == '+') {
				start = 1;
			}
		}
		SPCPPL_ASSERT(!str.empty());

		std::size_t firstBlockEnd = str.size() % digits;
		if (firstBlockEnd < start) {
			firstBlockEnd += digits;
		}

		auto expectedLength = divideCeil<std::size_t>(str.size() - start, digits);
		number.reserve(expectedLength);
		//@todo[c++17]: use std::string_view + substr
		number.push_back(stringBlockToInt(make_range(str.begin() + start, str.begin() + firstBlockEnd)));
		for (auto blockStart = str.begin() + firstBlockEnd; blockStart != str.end();) {
			auto blockEnd = blockStart + digits;
			number.push_back(stringBlockToInt(make_range(blockStart, blockEnd)));
			blockStart = blockEnd;
		}

		SPCPPL_ASSERT(number.size() == expectedLength);

		reverse(number);
		removeLeadingZeroes();
	}

	template <typename T, typename E = enable_if_t<IsSaneInteger<T>>>
	explicit BigInteger(T t) {
		if (t < 0) {
			isNegative = true;
			// Manual loop unrolling to avoid overflow when getting -t
			number.push_back(-(t % multiplier));
			t /= multiplier;
			t = -t;
		} else {
			isNegative = false;
		}
		while (t != 0) {
			number.push_back(t % multiplier);
			t /= multiplier;
		}
	}

	void operator*=(const BigInteger& rhs) {
		isNegative ^= rhs.isNegative;
		std::vector<int32_t> v(number.size() + rhs.number.size());
		for (size_t i: range(number.size())) {
			uint64_t carry = 0;
			for (size_t j: range(rhs.number.size())) {
				uint64_t current = static_cast<uint64_t>(rhs.number[j]) * static_cast<uint64_t>(number[i]) + carry + v[i + j];
				carry = current / multiplier;
				v[i + j] = static_cast<int32_t>(current % multiplier);
			}
			size_t position = rhs.number.size() + i;
			while (carry > 0) {
				uint64_t current = v[position] + carry;
				carry = current / multiplier;
				v[position] = static_cast<int32_t>(current % multiplier);
				++position;
			}
		}
		number = std::move(v);
		removeLeadingZeroes();
	}

	template <typename T, enable_if_t<IsSaneInteger<T> && (sizeof(T) > sizeof(int32_t))>* = nullptr>
	void operator*=(T t) {
		return *this *= BigInteger(t);
	}

	template <typename T, enable_if_t<IsSaneInteger<T> && sizeof(T) <= sizeof(int32_t)>* = nullptr>
	void operator*=(T t) {
		if (t == 0) {
			number.clear();
			isNegative = false;
			return;
		}
		auto signed_multiplier = static_cast<int64_t>(t);
		if (signed_multiplier < 0) {
			isNegative = !isNegative;
			signed_multiplier = -signed_multiplier;  // No overflow since sizeof(T) < sizeof(int64_t)
		}
		auto unsignedMultiplier = static_cast<uint64_t>(signed_multiplier);
		uint64_t carry = 0;
		for (auto& digit: number) {
			uint64_t current = static_cast<uint64_t>(digit) * unsignedMultiplier + carry;
			carry = current / multiplier;
			digit = static_cast<int32_t>(current % multiplier);
		}
		while (carry > 0) {
			number.push_back(static_cast<int32_t>(carry % multiplier));
			carry /= multiplier;
		}
		SPCPPL_ASSERT(number.empty() || number.back() != 0);
	}

	void operator+=(const BigInteger& rhs) {
		if (rhs.isZero()) {
			return;
		} else if (rhs.isNegative == isNegative) {
			assignAddAbsolute(rhs.number);
		} else {
			assignSubtractAbsolute(rhs.number);
		}
	}

	void operator+=(BigInteger&& rhs) {
		if (rhs.isZero()) {
			return;
		} else if (rhs.isNegative == isNegative) {
			assignAddAbsolute(rhs.number);
		} else {
			assignSubtractAbsolute(std::move(rhs.number));
		}
	}

	void operator-=(const BigInteger& rhs) {
		if (rhs.isZero()) {
			return;
		} else if (rhs.isNegative != isNegative) {
			assignAddAbsolute(rhs.number);
		} else {
			assignSubtractAbsolute(rhs.number);
		}
	}

	void operator-=(BigInteger&& rhs) {
		if (rhs.isZero()) {
			return;
		} else if (rhs.isNegative != isNegative) {
			assignAddAbsolute(rhs.number);
		} else {
			assignSubtractAbsolute(std::move(rhs.number));
		}
	}

	void shrink_to_fit() {
		number.shrink_to_fit();
	}

	void reserve(std::size_t length) {
		number.reserve(divideCeil<std::size_t>(length, digits));
	}

private:
	void assignAddAbsolute(const std::vector<std::int32_t>& rhsNumber) {
		ensureSize(rhsNumber.size());
		std::int32_t carry = 0;
		for (auto i: range(rhsNumber.size())) {
			number[i] += rhsNumber[i] + carry;
			carry = number[i] >= multiplier;
			if (carry) {
				number[i] -= multiplier;
			}
		}
		for (std::size_t i = rhsNumber.size(); carry > 0 && i < number.size(); ++i) {
			++number[i];
			carry = number[i] >= multiplier;
			if (carry) {
				number[i] -= multiplier;
			}
		}
		if (carry) {
			number.push_back(carry);
		}
		SPCPPL_ASSERT(number.back() != 0);
	}


	template <typename T>
	void assignSubtractAbsolute(T&& rhsNumber) {
		static_assert(std::is_same<std::decay_t<T>, std::vector<std::int32_t>>::value, "");
		if (detail::compare_less(number, rhsNumber)) {
			isNegative = !isNegative;
			std::vector<std::int32_t> copy_this = std::move(number);
			number = std::forward<T>(rhsNumber);
			SPCPPL_ASSERT(!detail::compare_less(number, rhsNumber));
			return assignSubtractAbsolute(copy_this);
		}
		int carry = 0;
		for (std::size_t i: range(rhsNumber.size())) {
			number[i] -= rhsNumber[i] + carry;
			carry = number[i] < 0;
			if (carry) {
				number[i] += multiplier;
			}
		}
		for (std::size_t i = rhsNumber.size(); carry > 0; ++i) {
			SPCPPL_ASSERT(i < number.size());
			number[i] -= carry;
			carry = number[i] < 0;
			if (carry) {
				number[i] += multiplier;
			}
		}
		removeLeadingZeroes();
	}

	template <typename Str>
	std::int32_t stringBlockToInt(const Str& str) {
		std::int32_t result = 0;
		for (char c: str) {
			SPCPPL_ASSERT(c >= 0 || c <= 9);
			result *= 10;
			result += c - '0';
		}
		return result;
	}

	void removeLeadingZeroes() {
		while (!number.empty() && number.back() == 0) {
			number.pop_back();
		}
		if (number.empty()) {
			isNegative = false;
		}
	}

	void ensureSize(std::size_t size) {
		if (number.size() < size) {
			number.resize(size);
		}
	}

	bool isZero() const {
		return number.empty();
	}

	static constexpr int digits = 9;
	static constexpr std::int32_t multiplier = 1'000'000'000;

	// todo: measure performance with uint32_t instead
	std::vector<std::int32_t> number;
	bool isNegative;

	friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
	friend std::ostream& operator<<(std::ostream& lhs, const BigInteger& rhs);
};

//todo: comparison with integers directly
bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
	if (lhs.isNegative && !rhs.isNegative) {
		return true;
	}
	else if (!lhs.isNegative && rhs.isNegative) {
		return false;
	}
	else if (lhs.isNegative) {
		return detail::compare_less(rhs.number, lhs.number);
	} else {
		return detail::compare_less(lhs.number, rhs.number);
	}
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
	return rhs < lhs;
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
	return !(lhs > rhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
	return !(lhs < rhs);
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
	return lhs.number == rhs.number && lhs.isNegative == rhs.isNegative;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
	return !(lhs == rhs);
}

BigInteger operator+(BigInteger lhs, const BigInteger& rhs) {
	lhs += rhs;
	return lhs;
}

BigInteger operator-(BigInteger lhs, const BigInteger& rhs) {
	lhs -= rhs;
	return lhs;
}

// todo: separate function for const& and && cases
BigInteger operator*(BigInteger lhs, const BigInteger& rhs) {
	lhs *= rhs;
	return lhs;
}

template <typename T, typename E = enable_if_t<IsSaneInteger<T>>>
BigInteger operator*(BigInteger lhs, T rhs) {
	lhs *= rhs;
	return lhs;
}

template <typename T, typename E = enable_if_t<IsSaneInteger<T>>>
BigInteger operator*(T lhs, BigInteger rhs) {
	rhs *= lhs;
	return rhs;
}

// todo: measure performance vs building string
std::ostream& operator<<(std::ostream& lhs, const BigInteger& rhs) {
	if (rhs.number.empty()) {
		return lhs << '0';
	}
	if (rhs.isNegative) {
		lhs << '-';
	}
	lhs << rhs.number.back();
	for (auto i: downrange(rhs.number.size() - 1)) {
		lhs << std::setfill('0') << std::setw(BigInteger::digits) << rhs.number[i];
	}
	return lhs;
}

std::istream& operator>>(std::istream& lhs, BigInteger& rhs) {
	std::string string;
	lhs >> string;
	rhs = BigInteger(string);
	return lhs;
}
