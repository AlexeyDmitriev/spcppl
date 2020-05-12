#pragma once

struct FunctionIdentity {
	template<typename T>
	constexpr T&& operator()(T&& t) const noexcept {
		return std::forward<T>(t);
	}
};
