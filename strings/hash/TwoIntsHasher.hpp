#pragma once

#include <string>
#include <vector>
#include <array>
#include "../../ranges/fors.hpp"
#include "../../numbers/primes.hpp"
#include "../../random/random.hpp"

class TwoIntsHasher {
public:

	static const uint64_t multiplier = 97;

	TwoIntsHasher(const std::string& s) {
		ensureLength(s.length());
		for (std::size_t j = 0; j < 2; ++j) {
			hashes[j].resize(s.length() + 1);
			for (std::size_t i: range(s.size())) {
				hashes[j][i + 1] = (hashes[j][i] * multiplier + s[i]) % modules[j];
			}
		}
	}

	uint64_t hash(std::size_t from, std::size_t to) const {
		SPCPPL_ASSERT(from <= to);
		return (oneHash(from, to, 0) << 32ULL) | (oneHash(from, to, 1));
	}

private:

	uint64_t oneHash(std::size_t from, std::size_t to, std::size_t index) const {
		uint64_t result = hashes[index][to] - hashes[index][from] * powers[index][to - from] % modules[index];
		if (result >= modules[index]) {
			result += modules[index];
		}
		return result;
	}

	static void ensureLength(std::size_t length) {
		for (std::size_t i = 0; i < 2; ++i) {
			std::vector<uint64_t>& powersArray = powers[i];
			powersArray.reserve(length + 1);
			while (powersArray.size() < length + 1) {
				powersArray.push_back(powersArray.back() * multiplier % modules[i]);
			}
		}
	}

	static std::array<std::vector<uint64_t>, 2> powers;
	std::array<std::vector<uint64_t>, 2> hashes;

	static uint64_t randomBigPrime() {
		return nextPrime(randomInteger(1000000000, 2000000000));
	}

	static const std::array<uint64_t, 2> modules;
};

std::array<std::vector<uint64_t>, 2> TwoIntsHasher::powers = {{{1}, {1}}};
const std::array<uint64_t, 2> TwoIntsHasher::modules = {{randomBigPrime(), randomBigPrime()}};
