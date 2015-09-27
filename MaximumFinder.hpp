#pragma once

#include <functional>
#include "MinimumFinder.hpp"

template <typename K, typename V>
using MaximumFinder = MinimumFinder<K, V, std::greater<V>>;
