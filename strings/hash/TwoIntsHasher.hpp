#pragma once

#include <string>
#include <vector>
#include <array>
#include "../../ranges/fors.hpp"
#include "../../numbers/primes.hpp"
#include "../../random/random.hpp"

class TwoIntsHasher {
public:

	static const unsigned long long multiplier = 97;

	TwoIntsHasher(const std::string& s) {
		for (std::size_t j = 0; j < 2; ++j) {
			hashes[j].resize(s.length() + 1);
			ensureLength(s.length());
			for (std::size_t i: range(s.size())) {
				hashes[j][i + 1] = (hashes[j][i] * multiplier + s[i]) % modules[j];
			}
		}
	}

	unsigned long long hash(std::size_t from, std::size_t to) {
		SPCPPL_ASSERT(from <= to);
		return (oneHash(from, to, 0) << 32ULL) | (oneHash(from, to, 1));
	}

private:

	unsigned long long oneHash(std::size_t from, std::size_t to, std::size_t index) {
		auto result = hashes[index][to] - hashes[index][from] * powers[index][to - from] % modules[index];
		if (result >= modules[index]) {
			result += modules[index];
		}
		return result;
	}

	static void ensureLength(std::size_t length) {
		for (std::size_t i = 0; i < 2; ++i) {
			std::vector<unsigned long long>& powersArray = powers[i];
			powersArray.reserve(length + 1);
			while (powersArray.size() < length + 1) {
				powersArray.push_back(powersArray.back() * multiplier % modules[i]);
			}
		}
	}

	static std::array<std::vector<unsigned long long>, 2> powers;
	std::array<std::vector<unsigned long long>, 2> hashes;

	static long long randomBigPrime() {
		return nextPrime(randomInteger(1000000000, 2000000000));
	}

	static const std::array<long long, 2> modules;
};

std::array<std::vector<unsigned long long>, 2> TwoIntsHasher::powers = {{{1}, {1}}};
const std::array<long long, 2> TwoIntsHasher::modules = {randomBigPrime(), randomBigPrime()};
