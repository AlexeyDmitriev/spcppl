#pragma once

#include <vector>
#include <spcppl/ranges/fors.hpp>

template <typename T>
class VectorVectorBaseGraph {
public:
	using Edge = T;
	using Vertex = std::size_t;

	explicit VectorVectorBaseGraph(std::size_t n): g(n) {
	}

	template <typename U>
	using Collection = std::vector<U>;

	template <typename U>
	Collection<U> getCollection(const U& defaultValue) const {
		return Collection<U>(g.size(), defaultValue);
	}

	IntegerRange<std::size_t> vertices() const {
		return range(g.size());
	}

	const std::vector<Edge>& outgoingEdges(Vertex vertex) const {
		return g[vertex];
	}
protected:
	std::vector<std::vector<Edge>> g;
};
