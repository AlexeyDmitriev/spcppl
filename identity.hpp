#pragma once

#include <type_traits>

template<typename T, typename Enable = std::true_type>
struct impl__IdentityHelper {
	static T identity();
	static T identity(const T&) {
		return identity();
	}
};

template<typename T>
T impl__IdentityHelper<T, typename std::is_arithmetic<T>::type>::identity() {
	return 1;
}

template<typename T>
T identity(const T& sample) {
	return impl__IdentityHelper<T>::identity(sample);
}

template <typename T>
T identity() {
	return impl__IdentityHelper<T>::identity();
}
