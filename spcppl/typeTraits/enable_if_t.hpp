#pragma once

#include <type_traits>

template <bool b, typename T = void>
//todo[c++14] use std::enable_if_t
using enable_if_t = typename std::enable_if<b, T>::type;
