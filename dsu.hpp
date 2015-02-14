#include <vector>
#include <cstddef>

class DSU {
public:
	DSU(size_t n): dsu(n) {
		for (size_t i = 0; i < n; ++i) {
			dsu[i] = i;
		}
	}

	size_t getSet(size_t v) {
		if (v == dsu[v]) {
			return v;
		}
		return dsu[v] = getSet(dsu[v]);
	}

	void unite(size_t u, size_t v) {
		u = getSet(u);
		v = getSet(v);
		dsu[v] = u;
	}
private:
	std::vector<size_t> dsu;
};
