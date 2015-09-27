#pragma once

#include <iostream>
#include <cstdlib>

#ifndef SPCPPL_IGNORE_ASSERTS

void assert_re(bool value) {
	if (!value) {
		std::exit(1);
	}
}

void assert_tl(bool value) {
	if (!value) {
		while (true) {
		}
	}
}

void assert_wa(bool value) {
	if (!value) {
		std::cout << "karamba";
		std::exit(0);
	}
}

#else
	#define assert_re(x)
	#define assert_tl(x)
	#define assert_wa(x)
#endif
