#pragma once

#include <vector>
#include <limits>
#include <functional>
#include <utility>
#include <queue>
#include <spcppl/ranges/fors.hpp>

template <typename FlowSize, typename CostSize>
struct CostFlow {
	FlowSize flow;
	CostSize cost;
};

template <typename FlowSize, typename CostSize>
class MinCostFlow {
	struct Edge {
		std::size_t from, to;
		FlowSize cap;
		FlowSize flow;
		CostSize cost;
	};
public:
	explicit MinCostFlow(std::size_t n): g(n) {

	}

	void addEdge(std::size_t from, std::size_t to, FlowSize capacity, CostSize cost) {
		SPCPPL_ASSERT(from < g.size() && to < g.size());
		Edge edge = {from, to, capacity, 0, cost};
		g[from].push_back(edges.size());
		edges.push_back(edge);

		Edge backwardEdge = {to, from, 0, 0, -cost};
		g[to].push_back(edges.size());
		edges.push_back(backwardEdge);
	}

	Edge getEdge(std::size_t id) {
		SPCPPL_ASSERT(id < edges.size());
		return edges[id];
	}

	std::size_t edgesCount() const {
		return edges.size();
	}

	template <typename Strategy>
	CostFlow<FlowSize, CostSize> findFlow(std::size_t s, std::size_t t, Strategy strategy) {
		SPCPPL_ASSERT(s < g.size());
		SPCPPL_ASSERT(t < g.size());
		SPCPPL_ASSERT(s != t);
		CostSize cost = 0;
		FlowSize flow = 0;
		std::size_t n = g.size();
		std::vector<CostSize> potential(n);
		const std::size_t NO_PARENT = std::numeric_limits<std::size_t>::max();
		{
			std::vector<std::size_t> p(n, NO_PARENT);
			std::vector<CostSize> d(n);
			d[s] = 0;
			p[s] = s;
			bool changed = true;
			while (changed) {
				changed = false;
				for (auto i: range(edges.size())) {
					Edge& e = edges[i];
					if (e.cap == e.flow || p[e.from] == -1) {
						continue;
					}
					if (p[e.to] == -1 || d[e.to] > d[e.from] + e.cost) {
						d[e.to] = d[e.from] + e.cost;
						p[e.to] = i;
						changed = true;
					}
				}
			}
			potential = std::move(d);
		}
		while (true) {
			std::vector<CostSize> d(n);
			std::vector<std::size_t> p(n, NO_PARENT);

			using QueueType = std::pair<CostSize, std::size_t>;
			std::priority_queue<QueueType, std::vector<QueueType>, std::greater<QueueType>> q;

			q.push(std::make_pair(0, s));

			while (!q.empty()) {
				std::size_t v = q.top().second;
				CostSize oldD = q.top().first;
				q.pop();
				if (oldD != d[v]) {
					continue;
				}
				for (std::size_t id: g[v]) {
					Edge& e = edges[id];
					if (e.to == s) {
						continue;
					}
					if (e.cap > e.flow) {
						SPCPPL_ASSERT(e.cost + potential[e.from] - potential[e.to] >= 0);
						CostSize newd = d[v] + e.cost + potential[e.from] - potential[e.to];
						if (p[e.to] == NO_PARENT || d[e.to] > newd) {
							d[e.to] = newd;
							p[e.to] = id;
							q.push(std::make_pair(d[e.to], e.to));
						}
					}
				}
			}

			if (p[t] == NO_PARENT) {
				break;
			}

			std::size_t cur = t;
			FlowSize maxAdd = strategy.maximalAdditionFlow(flow, cost, potential[t] + d[t]);

			if (maxAdd == 0) {
				break;
			}

			while (cur != s) {
				Edge& e = edges[p[cur]];
				cur = e.from;
				maxAdd = std::min(maxAdd, e.cap - e.flow);
			}

			flow += maxAdd;
			cost += (potential[t] + d[t]) * maxAdd;
			cur = t;
			while (cur != s) {
				std::size_t id = p[cur];
				edges[id].flow += maxAdd;
				edges[id ^ 1].flow -= maxAdd;
				cur = edges[id].from;
			}

			for (auto i: range(n)) {
				if (p[i] != NO_PARENT) {
					potential[i] = potential[i] + d[i];
				}
			}
		}

		return {flow, cost};

	}

private:
	std::vector<std::vector<std::size_t>> g;
	std::vector<Edge> edges;
};
