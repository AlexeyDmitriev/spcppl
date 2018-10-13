#pragma once

#include <cstddef>
#include <vector>
#include <spcppl/assert.hpp>

template <typename T, typename Merge>
class LazyPointSegmentTree {
	using size_t = std::size_t;
	struct Node {
		T value;
		size_t l;
		size_t r;
	};

public:
	explicit LazyPointSegmentTree(
			size_t size,
			const T& defaultValue = T(),
			const Merge& merge = Merge()
	):
			size(size),
			defaultValue(defaultValue),
			merge(merge) {
		createNode();
	}

	template <typename Updater>
	void update(size_t index, Updater&& updater) {
		SPCPPL_ASSERT(index <= size);
		return internalUpdate(0, 0, size, index, std::forward<Updater>(updater));
	}

	T getResult(size_t l, size_t r) {
		SPCPPL_ASSERT(l <= r && r <= size);
		return internalGet(0, 0, size, l, r);
	}

private:
	void recalculate(size_t v) {
		if (nodes[v].l == 0) {
			nodes[v].value = nodes[nodes[v].r].value;
			return;
		}
		if (nodes[v].r == 0) {
			nodes[v].value = nodes[nodes[v].l].value;
			return;
		}
		nodes[v].value = merge(nodes[nodes[v].l].value, nodes[nodes[v].r].value);
	}

	template <typename Updater>
	void internalUpdate(size_t v, size_t vl, size_t vr, size_t index, Updater&& updater) {
		if (vr - vl == 1) {
			SPCPPL_ASSERT(vl == index);
			std::forward<Updater>(updater)(nodes[v].value);
			return;
		}
		size_t vm = vl + (vr - vl) / 2;
		if (index < vm) {
			if (nodes[v].l == 0) {
				size_t l = createNode();
				nodes[v].l = l;
			}
			internalUpdate(nodes[v].l, vl, vm, index, std::forward<Updater>(updater));
		} else {
			if (nodes[v].r == 0) {
				size_t r = createNode();
				nodes[v].r = r;
			}
			internalUpdate(nodes[v].r, vm, vr, index, std::forward<Updater>(updater));
		}
		recalculate(v);
	}

	T internalGet(size_t v, size_t vl, size_t vr, size_t l, size_t r) {
		if (r <= vl || l >= vr) {
			return defaultValue;
		}
		if (l <= vl && vr <= r) {
			return nodes[v].value;
		}
		size_t vm = vl + (vr - vl) / 2;
		return merge(
				nodes[v].l == 0 ? defaultValue : internalGet(nodes[v].l, vl, vm, l, r),
				nodes[v].r == 0 ? defaultValue : internalGet(nodes[v].r, vm, vr, l, r)
		);
	}

	size_t createNode() {
		size_t id = nodes.size();
		nodes.push_back({defaultValue, 0, 0});
		return id;
	}
	size_t size;
	T defaultValue;
	Merge merge;
	std::vector<Node> nodes;
};
