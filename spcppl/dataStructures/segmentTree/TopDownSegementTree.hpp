#pragma once

#include <cstddef>
#include <vector>
#include "SegementTreeBase.hpp"

template <typename T, typename Merge, typename Update, typename ApplyUpdate, typename MergeUpdates>
class TopDownSegmentTree: protected SegmentTreeBase<T, Merge> {
	using size_t = std::size_t;
public:
	template <typename R>
	explicit TopDownSegmentTree(
			const R& range,
			const T& defaultValue = T(),
			const Merge& merge = Merge(),
			const Update& defaultUpdate = Update(),
			const ApplyUpdate& applyUpdate = ApplyUpdate(),
			const MergeUpdates& mergeUpdates = MergeUpdates()
	):
			SegmentTreeBase<T, Merge>(range, defaultValue, merge),
			defaultUpdate(defaultUpdate),
			updates(shift << 1, defaultUpdate),
			applyUpdate(applyUpdate),
			mergeUpdates(mergeUpdates) {

	}

	void update(size_t l, size_t r, const Update& update) {
		SPCPPL_ASSERT(l <= r && r <= n);
		return internalUpdate(1, 0, shift, l, r, update);
	}

	T getResult(size_t l, size_t r) {
		SPCPPL_ASSERT(l <= r && r <= n);
		return internalGet(1, 0, shift, l, r);
	}

protected:
	using Base = SegmentTreeBase<T, Merge>;
	using Base::n;
	using Base::defaultValue;
	using Base::shift;
	using Base::values;
	using Base::merge;
private:

	void internalUpdate(size_t v, size_t vl, size_t vr, size_t l, size_t r, const Update& update) {
		if (r <= vl || l >= vr) {
			return;
		}
		if (l <= vl && vr <= r) {
			values[v] = applyUpdate(values[v], update, vl, vr);
			updates[v] = mergeUpdates(updates[v], update);
			return;
		}
		push(v, vl, vr);
		size_t vm = vl + (vr - vl) / 2;
		internalUpdate(2 * v, vl, vm, l, r, update);
		internalUpdate(2 * v + 1, vm, vr, l, r, update);
		this->recalculate(v);
	}

	T internalGet(size_t v, size_t vl, size_t vr, size_t l, size_t r) {
		if (r <= vl || l >= vr) {
			return defaultValue;
		}
		if (l <= vl && vr <= r) {
			return values[v];
		}
		push(v, vl, vr);
		size_t vm = vl + (vr - vl) / 2;
		return merge(
				internalGet(2 * v, vl, vm, l, r),
				internalGet(2 * v + 1, vm, vr, l, r)
		);
	}

	void push(size_t v, size_t vl, size_t vr) {
		size_t vm = vl + (vr - vl) / 2;
		values[2 * v] = applyUpdate(values[2 * v], updates[v], vl, vm);
		updates[2 * v] = mergeUpdates(updates[2 * v], updates[v]);
		values[2 * v + 1] = applyUpdate(values[2 * v + 1], updates[v], vm, vr);
		updates[2 * v + 1] = mergeUpdates(updates[2 * v + 1], updates[v]);

		updates[v] = defaultUpdate;
	}

	Update defaultUpdate;
	std::vector<Update> updates;
	ApplyUpdate applyUpdate;
	MergeUpdates mergeUpdates;
};
