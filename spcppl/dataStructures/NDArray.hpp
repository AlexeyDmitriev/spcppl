#pragma once

#include <cstddef>
#include <array>
#include <vector>
#include <type_traits>
#include <spcppl/typeTraits/enable_if_t.hpp>
#include <spcppl/assert.hpp>
#include <spcppl/ranges/fors.hpp>

template <typename T, std::size_t depth>
class NDArrayView {
public:
	using Ref = std::conditional_t<depth == 1, T&, NDArrayView<T, depth - 1>>;

	Ref operator[] (std::size_t index) const {
		return get_element_impl(index);
	}

	Ref front() const {
		return get_at_index(0);
	}

	Ref back() const {
		if (suffixSizes[0] == 0) {
			return front();
		}
		return get_at_index(suffixSizes[0] - (depth == 1 ? 1 : suffixSizes[1]));
	}

	operator NDArrayView<const T, depth>() const {
		return NDArrayView<const T, depth>(elements, suffixSizes);
	}
	NDArrayView(NDArrayView&&) = default;
	NDArrayView& operator= (const NDArrayView&) = delete;
	NDArrayView&& operator= (NDArrayView&&) = delete;

private:
	template <std::size_t d = depth, enable_if_t<d == 1>* = nullptr>
	T& get_element_impl(std::size_t index) const {
		return elements[index];
	}

	template <std::size_t d = depth, enable_if_t<d != 1>* = nullptr>
	NDArrayView<T, depth - 1> get_element_impl(std::size_t index) const {
		return NDArrayView<T, depth - 1>(elements + suffixSizes[1] * index, suffixSizes + 1);
	}

	template <std::size_t d = depth, enable_if_t<d == 1>* = nullptr>
	T& get_at_index(std::size_t index) const {
		return elements[index];
	}

	template <std::size_t d = depth, enable_if_t<d != 1>* = nullptr>
	NDArrayView<T, depth - 1> get_at_index(std::size_t index) const {
		return NDArrayView<T, depth - 1>(elements + index, suffixSizes + 1);
	}

	NDArrayView(T* elements, const std::size_t* suffixSizes):
			elements(elements),
			suffixSizes(suffixSizes) {
	}
	T* elements;
	const std::size_t* suffixSizes;

	template <typename U, std::size_t d>
	friend class NDArray;

	template <typename U, std::size_t d>
	friend class NDArrayView;

	template <typename U, std::size_t d>
	friend void assignView(NDArrayView<U, d> lhs, NDArrayView<U, d> rhs);
};

template <typename T, std::size_t depth>
void assignView(NDArrayView<T, depth> lhs, NDArrayView<T, depth> rhs) {
	SPCPPL_ASSERT(lhs.suffixSizes[0] == rhs.suffixSizes[0]);
	std::copy(rhs.elements, rhs.elements + lhs.suffixSizes[0], lhs.elements);
};

template <typename T, std::size_t d>
bool operator==(const NDArrayView<T, d>&, const NDArrayView<T, d>&) = delete;

template <typename T, std::size_t d>
bool operator!=(const NDArrayView<T, d>&, const NDArrayView<T, d>&) = delete;

template <typename T, std::size_t depth>
using NDArrayConstView = NDArrayView<const T, depth>;

template <typename T, std::size_t depth>
class NDArray {
public:
	using Ref = typename NDArrayView<T, depth>::Ref;

	NDArray(const std::array<std::size_t, depth>& sizes):
			suffixSizes(suffixProducts(sizes)),
			elements(suffixSizes[0]) {
	}

	NDArray(const std::array<std::size_t, depth>& sizes, const T& t):
			suffixSizes(suffixProducts(sizes)),
			elements(suffixSizes[0], t) {
	}

	Ref operator[] (std::size_t index) {
		return static_cast<NDArrayView<T, depth>>(*this)[index];
	}

	Ref operator[] (std::size_t index) const {
		return static_cast<NDArrayView<const T, depth>>(*this)[index];
	}

	operator NDArrayView<T, depth>() {
		return NDArrayView<T, depth>(elements.data(), suffixSizes.data());
	}

	operator NDArrayConstView<T, depth>() const {
		return NDArrayConstView<T, depth>(elements.data(), suffixSizes.data());
	}

	Ref front() {
		return static_cast<NDArrayView<T, depth>>(*this).front();
	}

	Ref front() const {
		return static_cast<NDArrayConstView<T, depth - 1>>(*this).front();
	}

	Ref back() {
		return static_cast<NDArrayView<T, depth>>(*this).back();
	}

	Ref back() const {
		return static_cast<NDArrayConstView<T, depth - 1>>(*this).back();
	}
private:
	static std::array<std::size_t, depth> suffixProducts(const std::array<std::size_t, depth>& sizes) {
		std::array<std::size_t, depth> result;
		std::size_t last = 1;
		for (std::size_t index: downrange(depth)) {
			last *= sizes[index];
			result[index] = last;
		}
		return result;
	}
	std::array<std::size_t, depth> suffixSizes;
	std::vector<T> elements;
};

template <typename T, typename... Args>
NDArray<T, sizeof...(Args)> makeArray(Args... sizes) {
	return NDArray<T, sizeof...(Args)>(
			std::array<std::size_t, sizeof...(Args)>{{
					static_cast<std::size_t>(sizes)...
			}}
	);
}

template <typename T, typename... Args>
NDArray<T, sizeof...(Args)> makeFilledArray(const T& value, Args... sizes) {
	return NDArray<T, sizeof...(Args)>(
			std::array<std::size_t, sizeof...(Args)>{{
					static_cast<std::size_t>(sizes)...
			}},
			value
	);
}
