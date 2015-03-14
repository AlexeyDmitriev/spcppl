#pragma once

#include <random>

typedef std::mt19937 impl__Random;

impl__Random& random_engine() {
	static std::random_device device;
	static impl__Random engine(device());
	return engine;
}

int randomInteger(int to) {
	std::uniform_int_distribution<int> d(0, to - 1);
	return d(random_engine());
}

int randomInteger(int from, int to) {
	return from + randomInteger(to - from);
}