#include <gtest/gtest.h>
#include <functional>
#include <spcppl/dataStructures/MinQueue.hpp>
#include <spcppl/random/random.hpp>
#include <spcppl/ranges/fors.hpp>
#include "../operator_size.hpp"

TEST(MinQueueTest, ReturnsOnlyElement) {
	MinQueue<int> queue;
	queue.push(42);
	EXPECT_EQ(queue.getMinimum(), 42);
}

TEST(MinQueueTest, ReturnCorrectSize) {
	MinQueue<int> queue;
	EXPECT_EQ(queue.size(), 0_size);
	queue.push(7);
	EXPECT_EQ(queue.size(), 1_size);
	queue.push(3);
	EXPECT_EQ(queue.size(), 2_size);
	queue.push(99);
	EXPECT_EQ(queue.size(), 3_size);
	queue.pop();
	EXPECT_EQ(queue.size(), 2_size);
}

TEST(MinQueueTest, ReturnsSmallestElement) {
	MinQueue<int> queue;
	queue.push(15);
	EXPECT_EQ(queue.getMinimum(), 15);
	queue.push(7);
	EXPECT_EQ(queue.getMinimum(), 7);
	queue.push(8);
	EXPECT_EQ(queue.getMinimum(), 7);
	queue.pop();
	EXPECT_EQ(queue.getMinimum(), 7);
	queue.pop();
	EXPECT_EQ(queue.getMinimum(), 8);
}

TEST(MinQueueTest, StressTest) {
	MinQueue<int> min_queue;
	std::deque<int> std_queue;
	
	for (auto _: range(100000)) {
		static_cast<void>(_);
		bool push = std_queue.empty() || randomInteger(2) == 0;
		if (push) {
			int value = randomInteger();
			min_queue.push(value);
			std_queue.push_back(value);
		} else {
			min_queue.pop();
			std_queue.pop_front();
		}
		ASSERT_EQ(min_queue.size(), std_queue.size());
		if (min_queue.size() > 0) {
			ASSERT_EQ(
					min_queue.getMinimum(),
					*std::min_element(std_queue.begin(), std_queue.end())
			);
		}
	}
}

TEST(MinQueueTest, ReturnsMaxElementWithGreater) {
	MinQueue<int, std::greater<int>> queue;
	queue.push(15);
	EXPECT_EQ(queue.getMinimum(), 15);
	queue.push(7);
	EXPECT_EQ(queue.getMinimum(), 15);
	queue.push(8);
	EXPECT_EQ(queue.getMinimum(), 15);
	queue.pop();
	EXPECT_EQ(queue.getMinimum(), 8);
	queue.pop();
	EXPECT_EQ(queue.getMinimum(), 8);
}

TEST(MinQueueTest, WorksWithMovyOnlyTypes) {
	MinQueue<std::unique_ptr<int>> queue;
	queue.push(std::make_unique<int>(3));
	queue.push(std::make_unique<int>(7));
	static_cast<void>(queue.getMinimum());
	queue.pop();
	queue.pop();
}
