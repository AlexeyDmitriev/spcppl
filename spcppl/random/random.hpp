#pragma once

#include <random>
#include "../assert.hpp"

typedef std::mt19937 impl__Random;

impl__Random& randomEngine() {
	static std::random_device device;
	static impl__Random engine(device());
	return engine;
}

int randomInteger() {
	std::uniform_int_distribution<int> d;
	return d(randomEngine());
}

int randomInteger(int to) {
	SPCPPL_ASSERT(to > 0);
	std::uniform_int_distribution<int> d(0, to - 1);
	return d(randomEngine());
}

int randomInteger(int from, int to) {
	return from + randomInteger(to - from);
}