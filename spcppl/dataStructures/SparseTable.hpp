#pragma once

#include <vector>
#include <spcppl/ranges/fors.hpp>
#include <spcppl/numbers/bits.hpp>

template <typename T, typename Operation>
class SparseTable {
public:
	explicit SparseTable(std::vector<T> elements, const Operation& operation = Operation(), const T& neutralValue = T()):
			operation(operation), neutralValue(neutralValue) {
		std::size_t n = elements.size();
		logarithms.resize(n + 1);
		for (std::size_t i = 2; i < logarithms.size(); ++i) {
			logarithms[i] = logarithms[i - 1];
			if (isPowerOf2(i)) {
				++logarithms[i];
			}
		}

		table.push_back(std::move(elements));
		table.resize(logarithms[n] + 1, std::vector<T>(n));

		for (auto i: range(static_cast<std::size_t>(1), table.size())) {
			for (std::size_t j = 0; j + (1 << i) <= n; ++j) {
				table[i][j] = this->operation(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
			}
		}
	}

	T getResult(std::size_t l, std::size_t r) const {
		SPCPPL_ASSERT(l <= r && r <= table[0].size());
		if (l == r) {
			return neutralValue;
		}
		auto log = logarithms[r - l];
		SPCPPL_ASSERT((1 << log) <= r - l);
		SPCPPL_ASSERT((1 << (log + 1)) >= r - l);
		return operation(table[log][l], table[log][r - (1 << log)]);
	}
private:
	std::vector<std::size_t> logarithms;
	std::vector<std::vector<T>> table;
	Operation operation;
	T neutralValue;
};
