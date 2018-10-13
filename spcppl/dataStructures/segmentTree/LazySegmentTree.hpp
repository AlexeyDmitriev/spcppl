#pragma once

#include <cstddef>
#include <vector>
#include <spcppl/assert.hpp>

template <typename T, typename Merge, typename Update, typename ApplyUpdate, typename MergeUpdates>
class LazySegmentTree {
	using size_t = std::size_t;
	struct Node {
		T value;
		Update update;
		size_t l;
		size_t r;
	};

public:
	explicit LazySegmentTree(
			size_t size,
			const T& defaultValue = T(),
			const Merge& merge = Merge(),
			const Update& defaultUpdate = Update(),
			const ApplyUpdate& applyUpdate = ApplyUpdate(),
			const MergeUpdates& mergeUpdates = MergeUpdates()
	):
			size(size),
			defaultValue(defaultValue),
			merge(merge),
			defaultUpdate(defaultUpdate),
			applyUpdate(applyUpdate),
			mergeUpdates(mergeUpdates) {
		createNode();
	}

	void update(size_t l, size_t r, const Update& update) {
		SPCPPL_ASSERT(l <= r && r <= size);
		return internalUpdate(0, 0, size, l, r, update);
	}

	T getResult(size_t l, size_t r) {
		SPCPPL_ASSERT(l <= r && r <= size);
		return internalGet(0, 0, size, l, r);
	}

private:
	void recalculate(size_t v) {
		nodes[v].value = merge(nodes[nodes[v].l].value, nodes[nodes[v].r].value);
	}

	void internalUpdate(size_t v, size_t vl, size_t vr, size_t l, size_t r, const Update& update) {
		if (r <= vl || l >= vr) {
			return;
		}
		if (l <= vl && vr <= r) {
			nodes[v].value = applyUpdate(nodes[v].value, update, vl, vr);
			nodes[v].update = mergeUpdates(nodes[v].update, update);
			return;
		}
		push(v, vl, vr);
		size_t vm = vl + (vr - vl) / 2;
		internalUpdate(nodes[v].l, vl, vm, l, r, update);
		internalUpdate(nodes[v].r, vm, vr, l, r, update);
		recalculate(v);
	}

	T internalGet(size_t v, size_t vl, size_t vr, size_t l, size_t r) {
		if (r <= vl || l >= vr) {
			return defaultValue;
		}
		if (l <= vl && vr <= r) {
			return nodes[v].value;
		}
		push(v, vl, vr);
		size_t vm = vl + (vr - vl) / 2;
		return merge(
				internalGet(nodes[v].l, vl, vm, l, r),
				internalGet(nodes[v].r, vm, vr, l, r)
		);
	}

	void push(size_t v, size_t vl, size_t vr) {
		size_t vm = vl + (vr - vl) / 2;
		size_t l = nodes[v].l;
		size_t r = nodes[v].r;
		if (l == 0) {
			l = createNode();
			r = createNode();
			nodes[v].l = l;
			nodes[v].r = r;
		}
		nodes[l].value = applyUpdate(nodes[l].value, nodes[v].update, vl, vm);
		nodes[l].update = mergeUpdates(nodes[l].update, nodes[v].update);
		nodes[r].value = applyUpdate(nodes[r].value, nodes[v].update, vm, vr);
		nodes[r].update = mergeUpdates(nodes[r].update, nodes[v].update);

		nodes[v].update = defaultUpdate;
	}

	size_t createNode() {
		size_t id = nodes.size();
		nodes.push_back({defaultValue, defaultUpdate, 0, 0});
		return id;
	}
	size_t size;
	T defaultValue;
	Merge merge;
	Update defaultUpdate;
	ApplyUpdate applyUpdate;
	MergeUpdates mergeUpdates;
	std::vector<Node> nodes;
};
