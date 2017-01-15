#pragma once

#include <cstddef>
#include <string>
#include <algorithm>
#include <spcppl/assert.hpp>

template <typename Hasher>
class StringHash {
public:
	StringHash(std::string s): hasher(s), s(std::move(s)) {

	}

	uint64_t hash(std::size_t from, std::size_t to) const {
		return hasher.hash(from, to);
	}

	uint64_t prefixHash(std::size_t to) const {
		return hasher.hash(0, to);
	}

	uint64_t suffixHash(std::size_t from) const {
		return hasher.hash(from, s.size());
	}

	uint64_t hash() const {
		return hasher.hash(0, s.size());
	}

	bool less(std::size_t l1, std::size_t r1, std::size_t l2, std::size_t r2) {
		SPCPPL_ASSERT(l1 <= r1 && l2 <= r2);
		std::size_t min_len = std::min(r1 - l1, r2 - l2);
		if (s[l1] != s[l2]) {
			return s[l1] < s[l2];
		}
		if (hash(l1, l1 + min_len) == hash(l2, l2 + min_len)) {
			return r2 - l2 > r1 - l1;
		}
		std::size_t l = 0, r = min_len;
		while(r - l > 1) {
			std::size_t m = (r + l) / 2;
			if (hash(l1, l1 + m) == hash(l2, l2 + m)) {
				l = m;
			} else {
				r = m;
			}
		}

		auto res2 = s[l1 + l] < s[l2 + l];
		return res2;
	}

private:
	Hasher hasher;
	std::string s;
};
