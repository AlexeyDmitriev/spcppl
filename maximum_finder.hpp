#pragma once

#include <functional>
#include "minimum_finder.hpp"

template<typename K, typename V>
using MaximumFinder = MinimumFinder<K, V, std::greater<V>>;