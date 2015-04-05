#include <vector>
#include "assert.hpp"
#include "ranges/wrappers.hpp"

template <typename T>
class CoordinateMinimizer {
public:
	CoordinateMinimizer() {

	}

	template <typename R>
	explicit CoordinateMinimizer(const R& range) : values(range.begin(), range.end()) {
		finalize();
	}

	void finalize() {
		sort(values);
		#ifdef SPCPPL_DEBUG
			addingFinished = true;
		#endif
	}

	void add(const T& t) {
		SPCPPL_ASSERT(!addingFinished);
		values.push_back(t);
	}

	void add(T&& t) {
		SPCPPL_ASSERT(!addingFinished);
		values.push_back(std::move(t));
	}

	std::size_t find(const T& t) {
		SPCPPL_ASSERT(addingFinished);
		auto iterator = lower_bound(values, t);
		SPCPPL_ASSERT(iterator != values.end() && *iterator == t);
		return iterator - values.begin();
	}

private:
	std::vector<T> values;
	#ifdef SPCPPL_DEBUG
		bool addingFinished;
	#endif
};