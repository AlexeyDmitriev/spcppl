#pragma once

#include <functional>
#include <queue>
#include <utility>
#include <spcppl/assert.hpp>

template <typename T, typename Compare = std::less<T>>
class MinQueue {
public:
	explicit MinQueue(Compare compare = Compare()): size_(0), compare(compare) {
	}

	void push(const T& value) {
		push_impl(value);
	}

	void push(T&& value) {
		push_impl(std::move(value));
	}

	void pop() {
		SPCPPL_ASSERT(!queue.empty());
		if (--queue.front().second == 0) {
			queue.pop_front();
		}
		--size_;
	}

	std::size_t size() const {
		return size_;
	}

	const T& getMinimum() const {
		SPCPPL_ASSERT(!queue.empty());
		return queue.front().first;
	}

private:
	template <typename U>
	void push_impl(U&& value) {
		static_assert(std::is_same<U, T>::value || std::is_same<U, const T&>::value, "");
		size_t elementsWithFixedMin = 1;
		while (!queue.empty() && !compare(queue.back().first, value)) {
			elementsWithFixedMin += queue.back().second;
			queue.pop_back();
		}
		queue.emplace_back(std::move(value), elementsWithFixedMin);
		++size_;
	}
	std::size_t size_;
	std::deque<std::pair<T, std::size_t>> queue;
	Compare compare;
};
