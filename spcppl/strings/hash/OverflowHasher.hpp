#pragma once

#include <string>
#include <vector>
#include <spcppl/ranges/fors.hpp>

class OverflowHasher {
public:
	static const unsigned long long multiplier = 97;

	OverflowHasher(const std::string& s): hashes(s.size() + 1) {
		ensureLength(s.length());
		for (std::size_t i: range(s.size())) {
			hashes[i + 1] = hashes[i] * multiplier + s[i];
		}
	}

	unsigned long long hash(std::size_t from, std::size_t to) const {
		SPCPPL_ASSERT(from <= to);
		return hashes[to] - hashes[from] * powers[to - from];
	}

private:

	static void ensureLength(std::size_t length) {
		powers.reserve(length + 1);
		while (powers.size() < length + 1) {
			powers.push_back(powers.back() * multiplier);
		}
	}

	static std::vector<unsigned long long> powers;
	std::vector<unsigned long long> hashes;
};

std::vector<unsigned long long> OverflowHasher::powers = {1};
