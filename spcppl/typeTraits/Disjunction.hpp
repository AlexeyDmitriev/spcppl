#pragma once

#include <type_traits>

// todo[c++17]: replace with std::disjunction_v
template <bool... Bools>
struct Disjunction : std::false_type {
};

template <bool First, bool... Others>
// todo[c++14] use bool_constant
struct Disjunction<First, Others...> : std::integral_constant<bool, First || Disjunction<Others...>::value> {

};

template <bool... Bools>
constexpr bool DisjunctionV = Disjunction<Bools...>::value;

static_assert(!DisjunctionV<>, "");
static_assert(!DisjunctionV<false, false>, "");
static_assert(DisjunctionV<true>, "");
static_assert(DisjunctionV<false, true>, "");
static_assert(DisjunctionV<true, false>, "");
static_assert(DisjunctionV<false, false, true, true>, "");
