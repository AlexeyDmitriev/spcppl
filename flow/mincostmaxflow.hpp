#pragma once

#include <limits>

struct MinCostMaxFlowStrategy {
	template <typename FlowSize, typename CostSize>
	FlowSize maximalAdditionFlow(const FlowSize&, const CostSize&, const CostSize&) {
		return std::numeric_limits<FlowSize>::max();
	}
};
