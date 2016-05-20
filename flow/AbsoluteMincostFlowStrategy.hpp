#pragma once

#include <limits>

struct AbsoluteMinCostFlowStrategy {
	template <typename FlowSize, typename CostSize>
	FlowSize maximalAdditionFlow(const FlowSize&, const CostSize&, const CostSize& currentCost) {
		return currentCost < 0 ? std::numeric_limits<FlowSize>::max() : 0;
	}
};
