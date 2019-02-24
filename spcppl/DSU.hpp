#pragma once

#include <vector>
#include <cstddef>
#include "assert.hpp"

class DSU {
public:
	explicit DSU(std::size_t n): dsu(n) {
		for (std::size_t i = 0; i < n; ++i) {
			dsu[i] = i;
		}
	}

	std::size_t getSet(std::size_t v) {
		SPCPPL_ASSERT(v < dsu.size());
		if (v == dsu[v]) {
			return v;
		}
		return dsu[v] = getSet(dsu[v]);
	}

	bool unite(std::size_t u, std::size_t v) {
		SPCPPL_ASSERT(u < dsu.size());
		SPCPPL_ASSERT(v < dsu.size());
		u = getSet(u);
		v = getSet(v);
		if (u == v) {
			return false;
		} else {
			dsu[v] = u;
			return true;
		}
	}

	std::size_t components() const {
		std::size_t count = 0;
		for (std::size_t i = 0; i < dsu.size(); ++i) {
			if (dsu[i] == i) {
				++count;
			}
		}
		return count;
	}

private:
	std::vector<std::size_t> dsu;
};
