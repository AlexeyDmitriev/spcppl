#pragma once

#include <functional>

template <typename K, typename V, typename Compare = std::less<V>>
class MinimumFinder {
public:
	MinimumFinder(K startKey, V startValue, Compare compare = Compare()):
			bestKey(startKey), bestValue(startValue), compare(compare) {

	}

	void addValue(const K& key, const V& value) {
		if (compare(value, bestValue)) {
			bestKey = key;
			bestValue = value;
		}
	}

	V currentValue() {
		return bestValue;
	}

	K currentKey() {
		return bestKey;
	}

private:
	K bestKey;
	V bestValue;

	Compare compare;
};