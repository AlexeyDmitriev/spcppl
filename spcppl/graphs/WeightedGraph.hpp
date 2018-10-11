#pragma once

#include "VectorVectorBaseGraph.hpp"

template <typename T>
class WeightedGraph: public VectorVectorBaseGraph<std::pair<std::size_t, T>> {
	using Base = VectorVectorBaseGraph<std::pair<std::size_t, T>>;
public:
	using Length = T;
	using Vertex = typename Base::Vertex;
	using Edge = typename Base::Edge;
	using Base::g;
	explicit WeightedGraph(std::size_t n): Base(n) {}

	Vertex endOfEdge(Vertex, Edge edge) const {
		return edge.first;
	}

	void addEdge(Vertex from, Vertex to, const Length& l) {
		g[from].emplace_back(to, l);
	}

	Length edgeLength(Vertex, const Edge& e) const {
		return e.second;
	}
};
