#pragma once

#include <vector>
#include "../../typeTraits/IsContainer.hpp"
#include "../../ranges/fors.hpp"

template <typename T, typename Merge>
class SegmentTreeBase {
protected:
	SegmentTreeBase(std::size_t n, const T& defaultValue = T(), const Merge& merge = Merge()) :
			n(n),
			defaultValue(defaultValue),
			shift(calculateShift(n)),
			values(shift << 1, defaultValue),
			merge(merge) {

	}

	template <typename R, typename Enable = typename std::enable_if<IsContainer<R>::value>::type>
	SegmentTreeBase(const R& range, const T& defaultValue = T(), const Merge& merge = Merge()) :
			SegmentTreeBase(std::distance(std::begin(range), std::end(range)), defaultValue, merge) {
		std::copy(std::begin(range), std::end(range), values.begin() + shift);
		for (std::size_t index: downrange(shift, static_cast<std::size_t>(1))) {
			recalculate(index);
		}
	}

	static std::size_t calculateShift(std::size_t n) {
		std::size_t result = 1;
		while (result < n) {
			result <<= 1;
		}
		return result;
	}

	void recalculate(std::size_t index) {
		values[index] = merge(values[2 * index], values[2 * index + 1]);
	}

	std::size_t n;
	T defaultValue;
	std::size_t shift;
	std::vector <T> values;
	Merge merge;
};