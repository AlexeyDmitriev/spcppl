#pragma once

#include <vector>
#include <queue>
template <typename Graph>
std::vector<int> bfsDistances(const Graph& graph, const typename Graph::Vertex& from) {
	auto result = graph.getCollection(-1);
	std::queue<typename Graph::Vertex> q;
	q.push(from);
	result[from] = 0;
	while (!q.empty()) {
		const auto& v = q.front();
		for (const auto& e: graph.outgoingEdges(v)) {
			const auto& to = graph.endOfEdge(v, e);
			if (result[to] == -1) {
				result[to] = result[v] + 1;
				q.push(to);
			}
		}
		q.pop();
	}
	return result;
}
