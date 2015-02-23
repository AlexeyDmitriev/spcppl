#pragma once

#include <vector>
#include <cstddef>
#include "../identity.hpp"

bool isPrime(int n) {
	for(int i = 2; i * i <= n; ++i) {
		if(n % i == 0) {
			return false;
		}
	}
	return n >= 2;
}

