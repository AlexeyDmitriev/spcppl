#pragma once

#include "VectorVectorBaseGraph.hpp"

class SimpleGraph: public VectorVectorBaseGraph<std::size_t> {
public:
	explicit SimpleGraph(std::size_t n): VectorVectorBaseGraph(n) {}

	Vertex endOfEdge(Vertex, Edge edge) const {
		return edge;
	}

	void addEdge(Vertex from, Vertex to) {
		g[from].push_back(to);
	}
};
