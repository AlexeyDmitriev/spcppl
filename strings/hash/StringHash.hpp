#pragma once

#include <cstddef>
#include <string>

template <typename Hasher>
class StringHash {
public:
	StringHash(const std::string& s) : hasher(s) {

	}

	unsigned long long hash(std::size_t from, std::size_t to) {
		return hasher.hash(from, to);
	}

	unsigned long long prefixHash(std::size_t to) {
		return hasher.hash(0, to);
	}

	unsigned long long suffixHash(std::size_t from) {
		return hasher.hash(from, hasher.size());
	}

	unsigned long long hash() {
		return hasher.hash(0, hasher.size());
	}

private:
	Hasher hasher;
};
