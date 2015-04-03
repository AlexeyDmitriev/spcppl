#pragma once

template <typename FlowSize>
struct FixedFlowMinCostStrategy {
	FixedFlowMinCostStrategy(FlowSize maxFlow): maxFlow(maxFlow) {

	}
	template <typename CostSize>
	FlowSize maximalAdditionFlow(const FlowSize& currentFlow, const CostSize&, const CostSize&) {
		return maxFlow - currentFlow;
	}
private:
	FlowSize maxFlow;
};