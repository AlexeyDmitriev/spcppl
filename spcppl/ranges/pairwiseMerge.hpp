#pragma once

#include <utility>

template <typename Range, typename Function>
void pairwiseMerge(Range& range, Function function) {
	auto output = range.begin();
	auto end = range.end();
	if (output == end) {
		return;
	}
	auto current = output;
	++current;
	for (;current != end; ++current) {
		if (!function(*output, *current)) {
			++output;
			*output = std::move(*current);
		}
	}

	++output;
	range.erase(output, end);
}
