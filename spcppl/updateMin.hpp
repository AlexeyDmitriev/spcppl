#include <algorithm>

template <typename T>
void updateMin(T& oldValue, const T& newValue) {
	if (newValue < oldValue) {
		oldValue = newValue;
	}
}

template <typename T>
void updateMax(T& oldValue, const T& newValue) {
	if (oldValue < newValue) {
		oldValue = newValue;
	}
}
