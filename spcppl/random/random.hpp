#pragma once

#include <random>
#include <spcppl/assert.hpp>

namespace impl {
using Random = std::mt19937;
}  // namespace impl

inline impl::Random& randomEngine() {
	static std::random_device device;
	static impl::Random engine(device());
	return engine;
}

inline int randomInteger() {
	std::uniform_int_distribution<int> d;
	return d(randomEngine());
}

inline int randomInteger(int to) {
	SPCPPL_ASSERT(to > 0);
	std::uniform_int_distribution<int> d(0, to - 1);
	return d(randomEngine());
}

inline int randomInteger(int from, int to) {
	return from + randomInteger(to - from);
}
