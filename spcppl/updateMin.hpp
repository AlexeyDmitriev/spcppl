#include <algorithm>

template <typename T>
bool updateMin(T& oldValue, const T& newValue) {
	if (newValue < oldValue) {
		oldValue = newValue;
		return true;
	}
	return false;
}

template <typename T>
bool updateMax(T& oldValue, const T& newValue) {
	if (oldValue < newValue) {
		oldValue = newValue;
		return true;
	}
	return false;
}
