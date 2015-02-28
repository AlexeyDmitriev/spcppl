#pragma once

#include <vector>
#include <cstddef>

class DSU {
public:
	DSU(std::size_t n): dsu(n) {
		for (std::size_t i = 0; i < n; ++i) {
			dsu[i] = i;
		}
	}

	std::size_t getSet(std::size_t v) {
		if (v == dsu[v]) {
			return v;
		}
		return dsu[v] = getSet(dsu[v]);
	}

	void unite(std::size_t u, std::size_t v) {
		u = getSet(u);
		v = getSet(v);
		dsu[v] = u;
	}
private:
	std::vector<std::size_t> dsu;
};
