#pragma once

#include <type_traits>
#include <spcppl/typeTraits/IsOneOf.hpp>

//todo[c++14] use remove_cv_t
//todo[c++17] use is_integral_v
//todo[c++17] use  variable template
template <typename T>
using IsSaneInteger = std::integral_constant<
		bool,
		std::is_integral<T>::value && !IsOneOf<typename std::remove_cv<T>::type, char, signed char, unsigned char, bool, char16_t, char32_t, wchar_t>::value
>;
