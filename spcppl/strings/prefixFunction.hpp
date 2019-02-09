#pragma once

#include <vector>
#include <cstddef>
#include <string>
#include <spcppl/ranges/fors.hpp>

std::vector<std::size_t> prefixFunction(const std::string& s) {
	auto n = s.size();
	std::vector<std::size_t> pi(n);
	for (auto i: range<std::size_t>(1, n)) {
		std::size_t j = pi[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = pi[j - 1];
		}
		if (s[i] == s[j]) {
			++j;
		}
		pi[i] = j;
	}
	return pi;
}

/**
 * Doesn't work with string containing null bytes
 */
bool isSubstring(const std::string& haystack, const std::string& needle) {
	auto pi = prefixFunction(needle + '\0' + haystack);
	for (auto value: pi) {
		if (value == needle.size()) {
			return true;
		}
	}
	return false;
}
