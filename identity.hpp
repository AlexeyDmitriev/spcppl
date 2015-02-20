#pragma once

#include <type_traits>

template <typename T>
T identity();

//FIXME: remove {} when CPP-1825 fixed.
template<typename T, typename Enable = std::true_type>
struct impl__IdentityHelper {
};

template <typename T>
struct impl__SampleIdentityHelper {
	static T identity(const T&) {
		return ::identity<T>();
	}
};

template<typename T>
struct impl__IdentityHelper<T, typename std::is_arithmetic<T>::type> {
	static T identity() {
		return 1;
	}
};

template<typename T>
T identity(const T& sample) {
	return impl__SampleIdentityHelper<T>::identity(sample);
}

template <typename T>
T identity() {
	return impl__IdentityHelper<T>::identity();
}
