#include <gtest/gtest.h>
#include <spcppl/binpow.hpp>

TEST(Binpow, Ints) {
	ASSERT_EQ(binpow(2, 5), 32);
	ASSERT_EQ(binpow(0, 10), 0);
	ASSERT_EQ(binpow(1, 43), 1);
	ASSERT_EQ(binpow(-3, 3), -27);
	ASSERT_EQ(binpow(-1, 1000), 1);
}

struct Int {
	int x;
	Int operator *= (Int rhs) {
		x += rhs.x;
		return *this;
	}
};

template <>
struct IdentityHelper<Int> {
	static Int identity() {
		return {0};
	}
};

TEST(Binpow, Custom) {
	ASSERT_EQ(binpow(Int{3}, 5).x, 15);
	ASSERT_EQ(binpow(Int{9}, 3).x, 27);
	ASSERT_EQ(binpow(Int{9}, 0).x, 0);
}

