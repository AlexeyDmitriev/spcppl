#include <spcppl/numbers/Zn.hpp>
#include <gtest/gtest.h>

using Z = ZnConst<5>;
TEST(Zn, Construction) {
	for (int i = 0; i <= 4; ++i) {
		EXPECT_EQ(Z::valueOf(i).intValue(), i);
	}
	EXPECT_EQ(Z::valueOf(128).intValue(), 3);
	EXPECT_EQ(Z::valueOf(-1).intValue(), 4);

	EXPECT_EQ(Z::valueOf(5LL).intValue(), 0);
}

TEST(Zn, DefaultConstruction) {
	EXPECT_EQ(Z().intValue(), 0);
}

TEST(Zn, SimpleOperations) {
	EXPECT_EQ(Z::valueOf(1) + Z::valueOf(2), Z::valueOf(3));
	EXPECT_EQ(Z::valueOf(2) * Z::valueOf(3), Z::valueOf(1));
	EXPECT_EQ(Z() * Z::valueOf(2), Z::valueOf(0));
}

TEST(Zn, EqualityWithIntegers) {
	EXPECT_EQ(Z::valueOf(2), 2);
	EXPECT_EQ(Z::valueOf(7), 2);
	EXPECT_EQ(Z::valueOf(2), 7);
	EXPECT_EQ(Z::valueOf(2), 7LL);
	EXPECT_EQ(Z::valueOf(2), static_cast<short>(7));
	EXPECT_EQ(Z::valueOf(2), 7U);

	EXPECT_NE(Z::valueOf(2), 1);
	EXPECT_NE(Z(), 42);
}

TEST(Zn, OperationsWithInteger) {
	EXPECT_EQ(Z::valueOf(2) + 3, 0);
	EXPECT_EQ(1 + Z::valueOf(2), 3);
	EXPECT_EQ(4 * Z::valueOf(3), -3);
	EXPECT_EQ(Z::valueOf(3) * 3, 9);
	EXPECT_EQ(1 / Z::valueOf(3), 2);
	EXPECT_EQ(Z::valueOf(2) / 4, 3);
}

TEST(Zn, DivisionIsInverseOfMultiplication) {
	for (int a = 0; a < 5; ++a) {
		for (int b = 1; b < 5; ++b) {
			EXPECT_EQ(Z::valueOf(a) / Z::valueOf(b) * Z::valueOf(b), a);
		}
	}
}
