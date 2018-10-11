#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <spcppl/assert.hpp>
#include <spcppl/ranges/fors.hpp>
#include <spcppl/functors/Min.hpp>
#include <spcppl/dataStructures/SparseTable.hpp>

class SuffixArray {
public:
	explicit SuffixArray(std::string s) {
		s += '\0';
		suffArray.resize(s.size());
		std::vector<std::size_t> head(std::max(s.size(), static_cast<std::size_t>(128)), 0);
		std::vector<std::size_t> color(s.size());
		for (char c: s) {
			SPCPPL_ASSERT(c >= 0);
			++head[c];
		}
		for (int i = 1; i < 128; ++i) {
			head[i] += head[i - 1];
		}
		for (int i = 127; i > 0; --i) {
			head[i] = head[i - 1];
		}
		head[0] = 0;
		for (auto i: range(s.size())) {
			suffArray[head[s[i]]] = i;
			++head[s[i]];
		}
		std::size_t numberOfClasses = 1;
		head[0] = 0;
		for (auto i: range(static_cast<std::size_t>(1), s.size())) {
			if (s[suffArray[i - 1]] != s[suffArray[i]]) {
				++numberOfClasses;
				head[numberOfClasses - 1] = i;
			}
			color[suffArray[i]] = numberOfClasses - 1;
		}

		std::vector<std::size_t> nextSufArray(s.size());
		std::vector<std::size_t> nextColor(s.size());
		for (std::size_t k = 1; k < s.size(); k *= 2) {
			for (auto suffix: suffArray) {
				std::size_t firstPartBeginning = suffix - k;
				if (suffix < k) {
					firstPartBeginning += s.size();
				}
				nextSufArray[head[color[firstPartBeginning]]] = firstPartBeginning;
				++head[color[firstPartBeginning]];
			}
			swap(suffArray, nextSufArray);

			std::size_t secondPartBeginning;
			std::pair<std::size_t, std::size_t> prevSuffClasses;
			std::pair<std::size_t, std::size_t> curSuffClasses {color.size(), 0};
			numberOfClasses = 0;

			for (auto pos: range(suffArray.size())) {
				prevSuffClasses = curSuffClasses;

				secondPartBeginning = suffArray[pos] + k;
				if (secondPartBeginning >= s.size()) {
					secondPartBeginning -= s.size();
				}
				curSuffClasses = std::make_pair(color[suffArray[pos]], color[secondPartBeginning]);

				if (curSuffClasses != prevSuffClasses) {
					++numberOfClasses;
					head[numberOfClasses - 1] = pos;
				}
				nextColor[suffArray[pos]] = numberOfClasses - 1;
			}

			swap(color, nextColor);

			if (numberOfClasses == s.size())
				break;
		}
		suffArray.erase(suffArray.begin());

		pos.resize(suffArray.size());
		for (std::size_t i = 0; i < suffArray.size(); ++i) {
			pos[suffArray[i]] = i;
		}
	}

	std::size_t getNthSuffix(std::size_t n) const {
		SPCPPL_ASSERT(n < suffArray.size());
		return suffArray[n];
	}

	std::size_t getPosition(std::size_t suffix) const {
		SPCPPL_ASSERT(suffix < suffArray.size());
		return pos[suffix];
	}

	std::size_t size() const {
		return pos.size();
	}
	
private:
	std::vector<std::size_t> suffArray;
	std::vector<std::size_t> pos;
};

class SuffixArrayWithLcp : public SuffixArray {
public:
	explicit SuffixArrayWithLcp(const std::string& s):
			SuffixArray(s),
			sparse(generateLCP(*this, s)) {

	}
	std::size_t lcp(std::size_t l, std::size_t r) {
		l = getPosition(l);
		r = getPosition(r);
		auto p = std::minmax(l, r);
		return lcpByPosition(p.first, p.second);
	}

	std::size_t lcpByPosition(std::size_t l, std::size_t r) {
		SPCPPL_ASSERT(l <= r && r < size());
		if (l == r) {
			return size() - getNthSuffix(l);
		}
		return sparse.getResult(l, r);
	}

private:
	static std::vector<std::size_t> generateLCP(const SuffixArray& base, const std::string& s) {
		std::size_t curLcp = 0;

		std::vector<std::size_t> lcp(s.size() - 1);
		for (std::size_t i = 0; i < s.size(); ++i) {
			std::size_t position = base.getPosition(i);
			if (position == s.size() - 1) {
				curLcp = 0;
				continue;
			}

			while (s[i + curLcp] == s[base.getNthSuffix(position + 1) + curLcp]) {
				++curLcp;
			}
			lcp[position] = curLcp;

			if (curLcp > 0)
				--curLcp;
		}
		return lcp;
	}
	SparseTable<std::size_t, Min> sparse;
};
