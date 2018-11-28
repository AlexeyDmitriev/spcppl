#pragma once

#include <cstddef>
#include <map>
#include <vector>
#include <spcppl/assert.hpp>
#include <spcppl/Bool.hpp>
#include <spcppl/ranges/fors.hpp>
#include <spcppl/DSU.hpp>
#include <utility>

// todo: support different types of queries
struct DynamicConnectivityQuery {
	std::size_t a;
	std::size_t b;
	std::size_t time;
};

struct TimedEdge {
	std::size_t a;
	std::size_t b;
	std::size_t beginTime;
	std::size_t endTime;
};

struct DynamicConnectivityTest {
	std::vector<DynamicConnectivityQuery> queries;
	std::vector<TimedEdge> edges;
	std::size_t timeRange;
};

class DynamicConnectivityTestBuilder {
public:
	void addEdge(std::size_t a, std::size_t b) {
		if (a > b) {
			std::swap(a, b);
		}
		edgeStart[{a, b}] = ++time;
	}

	void removeEdge(std::size_t a, std::size_t b) {
		if (a > b) {
			std::swap(a, b);
		}
		auto it = edgeStart.find({a, b});
		SPCPPL_ASSERT(it != edgeStart.end());
		edges.push_back({a, b, it->second, ++time});
		edgeStart.erase(it);
	}

	void addQuery(std::size_t a, std::size_t b) {
		queries.push_back({a, b, time});
	}

	DynamicConnectivityTest build() && {
		++time;
		for (auto& p : edgeStart) {
			edges.push_back({p.first.first, p.first.second, p.second, time});
		}
		edgeStart.clear();
		return DynamicConnectivityTest{
				std::move(queries),
				std::move(edges),
				time
		};
	}

private:
	using Edge = std::pair<std::size_t, std::size_t>;
	std::size_t time = 0;
	std::vector<DynamicConnectivityQuery> queries;
	std::vector<TimedEdge> edges;
	std::map<Edge, std::size_t> edgeStart;
};

class DynamicConnectivitySolver {
public:
	explicit DynamicConnectivitySolver(std::vector<DynamicConnectivityQuery>&& queries):
			queries(std::move(queries)) {
		answers.reserve(queries.size());
	}

	void solve(
			std::size_t l,
			std::size_t r,
			const std::vector<TimedEdge>& edges,
			std::size_t n
	) {
		if (answers.size() == queries.size() || queries[answers.size()].time >= r) {
			return;
		}
		if (edges.empty()) {
			while (answers.size() != queries.size() && queries[answers.size()].time < r) {
				const auto& query = queries[answers.size()];
				answers.push_back(query.a == query.b);
			}
			return;
		}

		DSU dsu(n);
		std::vector<TimedEdge> filteredEdges;
		for (auto& edge: edges) {
			if (edge.beginTime <= l && r <= edge.endTime) {
				dsu.unite(edge.a, edge.b);
			}
			else if (edge.endTime <= l || edge.beginTime >= r) {
				// no intersection
			}
			else {
				filteredEdges.push_back(edge);
			}
		}

		std::vector<Bool> hasEdges(n);
		for (auto& edge: filteredEdges) {
			SPCPPL_ASSERT(edge.a < n);
			SPCPPL_ASSERT(edge.b < n);
			hasEdges[dsu.getSet(edge.a)] = true;
			hasEdges[dsu.getSet(edge.b)] = true;
		}

		std::vector<std::size_t> color(n);
		std::size_t usedRealColors = 0;
		std::size_t lastUsedColor = dsu.components();
		for (auto i: range(n)) {
			if (dsu.getSet(i) == i) {
				if (hasEdges[dsu.getSet(i)]) {
					color[i] = usedRealColors++;
				}
				else {
					color[i] = --lastUsedColor;
				}
			}
		}

		for (auto i: range(n)) {
			color[i] = color[dsu.getSet(i)];
		}

		SPCPPL_ASSERT(usedRealColors == lastUsedColor);

		for (std::size_t i = answers.size(); i < queries.size() && queries[i].time < r; ++i) {
			if (queries[i].a < n) {
				queries[i].a = color[queries[i].a];
			}
			if (queries[i].b < n) {
				queries[i].b = color[queries[i].b];
			}
		}

		for (auto& edge: filteredEdges) {
			edge.a = color[edge.a];
			edge.b = color[edge.b];
		}

		auto m = (l + r) / 2;
		solve(l, m, filteredEdges, usedRealColors);
		solve(m, r, filteredEdges, usedRealColors);
	}

	std::vector<DynamicConnectivityQuery> queries;
	std::vector<Bool> answers;
};

std::vector<Bool> dynamicConnectivity(DynamicConnectivityTest test, std::size_t n) {
	auto x = DynamicConnectivitySolver(std::move(test.queries));
	x.solve(0, test.timeRange, test.edges, n);
	return std::move(x.answers);
}
