#pragma once

#include <type_traits>

//FIXME: remove {} when CPP-1825 fixed.
template<typename T, typename Enable = std::true_type>
struct impl__IdentityHelper {

};

template<typename T>
struct impl__IdentityHelper<T, typename std::is_arithmetic<T>::type> {
	static T identity(const T&) {
		return 1;
	}
};

template<typename T>
T identity(const T& sample) {
	return impl__IdentityHelper<T>::identity(sample);
}
