#pragma once

#include <vector>
#include <iterator>
#include "../../assert.hpp"
#include "../../ranges/fors.hpp"
#include "../../typeTraits/IsContainer.hpp"

template <typename T, typename Merge>
class BottomUpSegmentTree {
public:
	BottomUpSegmentTree(std::size_t n, const T& defaultValue = T(), const Merge& merge = Merge()) :
			n(n),
			defaultValue(defaultValue),
			shift(calculateShift(n)),
			tree(shift << 1, defaultValue),
			merge(merge) {

	}

	template <typename R, typename Enable = typename std::enable_if<IsContainer<R>::value>::type>
	BottomUpSegmentTree(const R& range, const T& defaultValue = T(), const Merge& merge = Merge()) :
			BottomUpSegmentTree(std::distance(std::begin(range), std::end(range)), defaultValue, merge) {
		std::copy(std::begin(range), std::end(range), tree.begin() + shift);
		for (std::size_t index: downrange(shift, static_cast<std::size_t>(1))) {
			recalculate(index);
		}
	}


	T getResult(std::size_t l, std::size_t r) const {
		SPCPPL_ASSERT(0 <= l && l <= r && r <= n);
		return internalGetResult(l + shift, r + shift);
	}

	template <typename Updater>
	void update(std::size_t index, const Updater& updater) {
		index += shift;
		updater(tree[index]);
		for (std::size_t parent = index / 2; parent > 0; parent /= 2) {
			recalculate(parent);
		}
	}

	void set(std::size_t index, const T& value) {
		return update(index, [&value](T& element) {
				element = value;
		});
	}

private:
	T internalGetResult(std::size_t l, std::size_t r) const {
		if (l == r) {
			return defaultValue;
		}
		if (l & 1) {
			return merge(tree[l], internalGetResult(l + 1, r));
		}
		if (r & 1) {
			return merge(internalGetResult(l, r - 1), tree[r - 1]);
		}
		return internalGetResult(l / 2, r / 2);
	}

	static std::size_t calculateShift(std::size_t n) {
		std::size_t result = 1;
		while (result < n) {
			result <<= 1;
		}
		return result;
	}

	void recalculate(std::size_t index) {
		tree[index] = merge(tree[2 * index], tree[2 * index + 1]);
	}

	std::size_t n;
	T defaultValue;
	std::size_t shift;
	std::vector <T> tree;
protected:
	Merge merge;
};