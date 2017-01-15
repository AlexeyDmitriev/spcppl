#pragma once

#include <vector>
#include <functional>
#include <queue>
#include <spcppl/functors/PositiveInfinity.hpp>
#include <spcppl/assert.hpp>

template <
		typename Graph,
		typename Length = typename Graph::Length,
		typename Vertex = typename Graph::Vertex
>
auto dijkstraDistances(
		const Graph& graph,
		const Vertex& start,
		const Length& infinity = PositiveInfinity<Length>()()
) -> decltype(graph.getCollection(infinity)) {
	auto used = graph.getCollection(char());
	auto distance = graph.getCollection(infinity);
	using QueueElement = std::pair<Length, Vertex>;
	std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> queue;
	queue.emplace(0, start);
	distance[start] = 0;
	while (!queue.empty()) {
		Vertex v = queue.top().second;
		SPCPPL_ASSERT(distance[v] == queue.top().first);
		queue.pop();
		if (used[v]) {
			continue;
		}
		used[v] = true;
		for (const auto& e: graph.outgoingEdges(v)) {
			const auto& to = graph.endOfEdge(v, e);
			Length newLength = distance[v] + graph.edgeLength(v, e);
			if (distance[to] > newLength) {
				distance[to] = newLength;
				queue.emplace(distance[to], to);
			}
		}
	}
	return distance;
};
