#pragma once

#include <type_traits>
#include <spcppl/typeTraits/Disjunction.hpp>

template <typename T, typename... Types>
// todo[c++17] use is_same_v
// todo[c++17] use variable template
using IsOneOf = Disjunction<std::is_same<T, Types>::value...>;
