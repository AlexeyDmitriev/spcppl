#pragma once

template <typename FlowSize>
struct FixedFlowMinCostStrategy {
	explicit FixedFlowMinCostStrategy(FlowSize maxFlow): maxFlow(maxFlow) {

	}

	template <typename CostSize>
	FlowSize maximalAdditionFlow(const FlowSize& currentFlow, const CostSize&, const CostSize&) {
		return maxFlow - currentFlow;
	}

private:
	FlowSize maxFlow;
};
