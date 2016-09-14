#include <gtest/gtest.h>
#include <spcppl/convolution.hpp>
#include <random>

TEST(Convolution, Small) {
	std::vector<int> v(8);
	v[2] = 10;
	v[5] = 1;
	v[3] = 3;
	std::vector<int> expectedAnswer(8);
	expectedAnswer[2] = 10;
	expectedAnswer[3] = 3 + 10;
	expectedAnswer[5] = 1;
	expectedAnswer[6] = 10;
	expectedAnswer[7] = 3 + 1 + 10;
	ASSERT_EQ(submasksSums(v), expectedAnswer);
}

std::vector<int> submasksSumsStupid(const std::vector<int>& v) {
	std::vector<int> results(v.size());
	for (std::size_t i = 0; i < v.size(); ++i) {
		for (std::size_t j = 0; j < v.size(); ++j) {
			if ((i & j) == j) {
				results[i] += v[j];
			}
		}
	}
	return results;
}

TEST(Convolution, Big) {
	std::mt19937 gen;
	std::vector<int> input(1 << 10);
	std::uniform_int_distribution<int> dist(-100, 100);
	for (std::size_t i = 0; i < (1 << 10); ++i) {
		input[i] = dist(gen);
	}
	
	ASSERT_EQ(submasksSums(input), submasksSumsStupid(input));
}
