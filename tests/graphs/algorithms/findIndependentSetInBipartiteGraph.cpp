#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <spcppl/Bool.hpp>
#include <spcppl/ranges/indices.hpp>
#include <spcppl/graphs/algorithms/findIndependentSetInBipartiteGraph.hpp>

bool independent(
		const std::vector<std::vector<std::size_t>>& graph,
		const std::pair<std::vector<std::size_t>, std::vector<std::size_t>>& set) {
	for (auto l: set.first) {
		for (auto r: set.second) {
			if (std::find(graph[l].begin(), graph[l].end(), r) != graph[l].end()) {
				return false;
			}
		}
	}
	return true;
}

TEST(IndependentSet, EmptyGraph) {
	std::vector<std::vector<std::size_t>> g(5);
	auto result = findIndependentSetInBipartiteGraph(g, 3);
	EXPECT_EQ(result.first, indices<std::size_t>(5));
	EXPECT_EQ(result.second, indices<std::size_t>(3));
}

TEST(IndependentSet, SimpleEdge) {
	std::vector<std::vector<std::size_t>> g(5);
	g[2] = {1};
	auto result = findIndependentSetInBipartiteGraph(g, 3);

	EXPECT_TRUE(independent(g, result));
	EXPECT_EQ(result.first.size() + result.second.size(), static_cast<std::size_t>(7));
}


void testFullGraph(std::size_t leftSize, std::size_t rightSize) {
	auto rightHalf = indices(rightSize);
	std::vector<std::vector<std::size_t>> graph(leftSize, rightHalf);
	auto result = findIndependentSetInBipartiteGraph(graph, rightSize);
	EXPECT_TRUE(independent(graph, result));
	EXPECT_EQ(result.first.size() + result.second.size(), std::max(leftSize, rightSize));
}

TEST(IndependentSet, FullGraph) {
	testFullGraph(3, 3);
	testFullGraph(3, 5);
	testFullGraph(5, 4);
}
