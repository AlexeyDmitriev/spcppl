#pragma once

#include <type_traits>
#include <spcppl/typeTraits/IsOneOf.hpp>

template <typename T>
//todo[c++14] use remove_cv_t
//todo[c++17] use is_integral_v
constexpr bool IsSaneInteger = std::is_integral<T>::value && !IsOneOf<typename std::remove_cv<T>::type, char, signed char, unsigned char, bool, char16_t, char32_t, wchar_t>;
