#pragma once

#include <type_traits>
#include <spcppl/typeTraits/Disjunction.hpp>

template <typename T, typename... Types>
// todo[c++17] use is_same_v
constexpr bool IsOneOf = DisjunctionV<std::is_same<T, Types>::value...>;
