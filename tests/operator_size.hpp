#pragma once

#include <cstddef>

inline std::size_t operator ""_size (unsigned long long value) {
	return static_cast<std::size_t>(value);
}
