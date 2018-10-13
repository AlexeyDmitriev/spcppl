#pragma once

#include <limits>
#include "MinCostFlow.hpp"

template <typename CostSize>
struct FixedCostMaxFlowStrategy {
	explicit FixedCostMaxFlowStrategy(CostSize maxCost): maxCost(maxCost) {

	}

	template <typename FlowSize>
	FlowSize maximalAdditionFlow(const FlowSize&, const CostSize& currentCost, const CostSize& additionalCost) {
		if (additionalCost <= 0) {
			return std::numeric_limits<FlowSize>::max();
		}
		return (maxCost - currentCost) / additionalCost;
	}

private:
	CostSize maxCost;
};
