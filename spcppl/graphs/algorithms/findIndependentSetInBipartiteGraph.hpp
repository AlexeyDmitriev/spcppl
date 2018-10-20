#pragma once

#include <vector>
#include <utility>
#include <spcppl/assert.hpp>
#include <spcppl/Bool.hpp>
#include <spcppl/ranges/fors.hpp>

namespace impl {

constexpr std::size_t noPair = std::numeric_limits<std::size_t>::max();

class MatchingFinder {
public:
	MatchingFinder(
			const std::vector<std::vector<std::size_t>>& graph,
			std::vector<std::size_t>& mt
	): graph(graph), mt(mt), used(graph.size()) {
	}

	bool tryPushAugumentingPath(std::size_t v) {
		if (used[v]) {
			return false;
		}
		used[v] = true;
		for (std::size_t i: range(graph[v].size())) {
			auto to = graph[v][i];
			if (mt[to] == noPair || tryPushAugumentingPath(mt[to])) {
				mt[to] = v;
				return true;
			}
		}
		return false;
	}

	void clearUsed() {
		std::fill(used.begin(), used.end(), false);
	}

private:
	const std::vector<std::vector<std::size_t>>& graph;
	std::vector<std::size_t>& mt;
	std::vector<Bool> used;
};

class IndependentSetFinder {
public:
	IndependentSetFinder(
			const std::vector<std::vector<std::size_t>>& graph,
			std::vector<std::size_t>& mt
	):
			graph(graph),
			mt(mt),
			inAnswerLeft(graph.size(), true),
			inAnswerRight(mt.size(), true),
			inMatchLeft(graph.size()) {
	}

	std::pair<std::vector<Bool>, std::vector<Bool>> find() {
		for (auto v: mt) {
			if (v != noPair) {
				inMatchLeft[v] = true;
				inAnswerLeft[v] = false;
			}
		}
		for (auto i: range(graph.size())) {
			if (!inMatchLeft[i]) {
				dfs(i);
			}
		}
		return {inAnswerLeft, inAnswerRight};
	}

private:
	void dfs(std::size_t v) {
		for (auto to: graph[v]) {
			if (inAnswerRight[to]) {
				inAnswerRight[to] = false;
				SPCPPL_ASSERT(mt[to] != noPair);
				SPCPPL_ASSERT(!inAnswerLeft[mt[to]]);
				inAnswerLeft[mt[to]] = true;
				dfs(mt[to]);
			}
		}
	}

	const std::vector<std::vector<std::size_t>>& graph;
	std::vector<std::size_t>& mt;
	std::vector<Bool> inAnswerLeft;
	std::vector<Bool> inAnswerRight;
	std::vector<Bool> inMatchLeft;
};

}  // namespace impl

std::pair<std::vector<std::size_t>, std::vector<std::size_t>> findIndependentSetInBipartiteGraph(
		const std::vector<std::vector<std::size_t>>& graph,
		std::size_t rightSize
) {
	std::size_t leftSize = graph.size();

	std::vector<std::size_t> mt(rightSize, impl::noPair);

	impl::MatchingFinder dfser(graph, mt);
	for (auto v: range(leftSize)) {
		dfser.clearUsed();
		dfser.tryPushAugumentingPath(v);
	}

	impl::IndependentSetFinder finder(graph, mt);
	auto maps = finder.find();

	auto indices = [](const std::vector<Bool>& map) {
		std::vector<std::size_t> result;
		result.reserve(map.size());
		for (auto index: range(map.size())) {
			if (map[index]) {
				result.push_back(index);
			}
		}
		return result;
	};
	return {
			indices(maps.first),
			indices(maps.second)
	};
}
