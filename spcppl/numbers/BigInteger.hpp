#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <spcppl/assert.hpp>
#include <spcppl/numbers/division.hpp>
#include <spcppl/ranges/Range.hpp>
#include <spcppl/ranges/wrappers.hpp>
#include <spcppl/typeTraits/IsSaneInteger.hpp>
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

	template <typename T, typename E = std::enable_if_t<IsSaneInteger<T>>>
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
	std::vector<std::int32_t> number;
	bool isNegative;

	friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
	friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
	friend std::ostream& operator<<(std::ostream& lhs, const BigInteger& rhs);
};

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
