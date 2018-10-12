#pragma once

#include <string>
#include <vector>
#include <array>
#include <spcppl/ranges/fors.hpp>
#include <spcppl/numbers/primes.hpp>
#include <spcppl/random/random.hpp>
#include <spcppl/numbers/Zn.hpp>

class TwoIntsHasher {
public:

	TwoIntsHasher(const std::string& s) {
		ensureLength(s.length());
		for (std::size_t j = 0; j < 2; ++j) {
			hashes[j].resize(s.length() + 1);
			for (std::size_t i: range(s.size())) {
				hashes[j][i + 1] = (hashes[j][i] * multipliers[j] + static_cast<int>(s[i]));
			}
		}
	}

	uint64_t hash(std::size_t from, std::size_t to) const {
		SPCPPL_ASSERT(from <= to);
		return (oneHash(from, to, 0) << 32ULL) | (oneHash(from, to, 1));
	}

private:
	struct Modulo {
		static int value;
	};
	using Z = Zn<Modulo>;

	uint64_t oneHash(std::size_t from, std::size_t to, std::size_t index) const {
		return static_cast<uint64_t>((hashes[index][to] - hashes[index][from] * powers[index][to - from]).intValue());
	}

	static void ensureLength(std::size_t length) {
		for (std::size_t i = 0; i < 2; ++i) {
			std::vector<Z>& powersArray = powers[i];
			powersArray.reserve(length + 1);
			while (powersArray.size() < length + 1) {
				powersArray.push_back(powersArray.back() * multipliers[i]);
			}
		}
	}

	static std::array<std::vector<Z>, 2> powers;
	std::array<std::vector<Z>, 2> hashes;

	static int32_t randomBigPrime() {
		return nextPrime(randomInteger(1000000000, 2000000000));
	}

	static const std::array<Z, 2> multipliers;
};

int TwoIntsHasher::Modulo::value = randomBigPrime();
std::array<std::vector<TwoIntsHasher::Z>, 2> TwoIntsHasher::powers = {{{TwoIntsHasher::Z::rawValueOf(1)}, {TwoIntsHasher::Z::rawValueOf(1)}}};

const std::array<TwoIntsHasher::Z, 2> TwoIntsHasher::multipliers = {{TwoIntsHasher::Z::rawValueOf(137), TwoIntsHasher::Z::rawValueOf(97)}};
