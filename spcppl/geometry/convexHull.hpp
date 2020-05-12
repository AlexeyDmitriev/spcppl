#pragma once

#include <spcppl/functors/FunctionIdentity.hpp>
#include <spcppl/ranges/wrappers.hpp>
#include <spcppl/geometry/Point2D.hpp>
#include <vector>
#include <iterator>

template <typename Collection, typename Proj = FunctionIdentity>
auto convexHull(Collection points, Proj proj = {}) {
	using T = typename Collection::value_type;
	LexicograficallyLess less;

	sort(points, [&](const auto& lhs, const auto& rhs) {
		return less(proj(lhs), proj(rhs));
	});

	std::vector<T> top;
	for (const auto& elem: points) {
		while (top.size() >= 2 &&
				((proj(top[top.size() - 1]) - proj(top[top.size() - 2])) * (proj(elem) - proj(top.back())) >= 0)) {
			top.pop_back();
		}
		top.push_back(elem);
	}
	std::vector<T> bottom;


	for (const auto& elem: points) {
		while (bottom.size() >= 2 &&
				((proj(bottom[bottom.size() - 1]) - proj(bottom[bottom.size() - 2])) * (proj(elem) - proj(bottom.back())) <= 0)) {
			bottom.pop_back();
		}
		bottom.push_back(elem);
	}
	bottom.insert(bottom.end(), std::next(top.rbegin()), prev(top.rend()));
	return bottom;
}
