#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include "../assert.hpp"
#include "../ranges/fors.hpp"
#include "../numbers/bits.hpp"

class BitSet {
	BitSet(std::size_t size): size(size), v(getUnderlyingSize(size)) {

	}

	BitSet operator|=(const BitSet& rhs) {
		SPCPPL_ASSERT(size == rhs.size);
		for (size_t i: range(v.size())) {
			v[i] |= rhs.v[i];
		}
		return *this;
	}

	BitSet operator&=(const BitSet& rhs) {
		SPCPPL_ASSERT(size == rhs.size);
		for (size_t i: range(v.size())) {
			v[i] &= rhs.v[i];
		}
		return *this;
	}

	BitSet operator^=(const BitSet& rhs) {
		SPCPPL_ASSERT(size == rhs.size);
		for (size_t i: range(v.size())) {
			v[i] ^= rhs.v[i];
		}
		return *this;
	}

	BitSet operator~() const& {
		auto copy = *this;
		copy.invert();
		return copy;
	}

	BitSet operator~()&& {
		invert();
		return *this;
	}

	bool empty() {
		for (uint32_t number: v) {
			if (number != 0) {
				return false;
			}
		}
		return true;
	}

	std::size_t leastBit() const {
		for (std::size_t i: range(v.size())) {
			if (v[i] != 0) {
				return i * 32 + leastSignificantBit(v[i]);
			}
		}
		return size;
	}

	BitSet& operator<<=(std::size_t rhs) {
		SPCPPL_ASSERT(rhs <= size);
		std::size_t bigShifts = rhs >> 5;
		std::memmove(&v[bigShifts], &v[0], bigShifts);
		std::memcpy(&v[0], 0, bigShifts);
		rhs &= 31;
		uint32_t add = 0;
		for (uint32_t& element: v) {
			uint32_t next = (element >> (32 - rhs));
			element <<= rhs;
			element ^= add;
			add = next;
		}
		return *this;
	}

	BitSet& operator>>=(std::size_t rhs) {
		SPCPPL_ASSERT(rhs <= size);
		std::size_t bigShifts = rhs >> 5;
		std::memmove(&v[0], &v[bigShifts], bigShifts);
		std::memcpy(&v[0] + size - bigShifts, 0, bigShifts);
		rhs &= 31;
		int32_t add = 0;
		for (std::size_t i: downrange(v.size())) {
			uint32_t next = (v[i] << rhs);
			v[i] >>= rhs;
			v[i] ^= add;
			add = next;
		}
		return *this;
	}

private:
	BitSet& invert() {
		for (size_t i: range(v.size())) {
			v[i] = ~v[i];
		}
		std::size_t lastBits = size & 31;
		if (size != 0) {
			v.back() &= (1 << lastBits) - 1;
		}
		return *this;
	}

	static std::size_t getUnderlyingSize(std::size_t size) {
		return (size + 31) >> 5;
	}

	std::vector<uint32_t> v;
	std::size_t size;

	friend bool operator==(const BitSet& a, const BitSet& b);
};

BitSet operator|(const BitSet& a, const BitSet& b) {
	BitSet copy = a;
	return copy |= b;
}

BitSet operator&(const BitSet& a, const BitSet& b) {
	BitSet copy = a;
	return copy &= b;
}

BitSet operator^(const BitSet& a, const BitSet& b) {
	BitSet copy = a;
	return copy ^= b;
}

BitSet operator<<=(const BitSet& a, std::size_t b) {
	BitSet copy = a;
	return copy <<= b;
}

BitSet operator>>=(const BitSet& a, std::size_t b) {
	BitSet copy = a;
	return copy >>= b;
}

bool operator==(const BitSet& a, const BitSet& b) {
	SPCPPL_ASSERT(a.size == b.size);
	return a.v == b.v;
}

bool operator!=(const BitSet& a, const BitSet& b) {
	return !(a == b);
}
