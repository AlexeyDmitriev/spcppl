#pragma once

#include <algorithm>
#include "ranges/fors.hpp"

template <typename T>
T workerStart(T all, int nodeId, int nodes) {
	SPCPPL_ASSERT(nodeId <= nodes);
	T everyone = all / nodes;
	T begin = everyone * nodeId;
	begin += std::min(static_cast<int>(all % nodes), nodeId);
	return begin;
}

template <typename T>
IntegerRange<T> workerRange(T all, int nodeId, int nodes) {
	return range(workerStart(all, nodeId, nodes), workerStart(all, nodeId + 1, nodes));
}