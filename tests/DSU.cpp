#include <gtest/gtest.h>
#include <spcppl/DSU.hpp>

TEST(DSU, Basics) {
	DSU dsu(5);
	dsu.unite(3, 1);
	dsu.unite(3, 4);

	ASSERT_EQ(dsu.getSet(1), dsu.getSet(3));
	ASSERT_EQ(dsu.getSet(1), dsu.getSet(4));
	ASSERT_NE(dsu.getSet(3), dsu.getSet(0));
	ASSERT_NE(dsu.getSet(3), dsu.getSet(2));
	ASSERT_NE(dsu.getSet(0), dsu.getSet(2));
}

TEST(DSU, Immidiate) {
	DSU dsu(3);
	ASSERT_EQ(dsu.getSet(0), static_cast<std::size_t>(0));
	ASSERT_EQ(dsu.getSet(1), static_cast<std::size_t>(1));
	ASSERT_EQ(dsu.getSet(2), static_cast<std::size_t>(2));
}

TEST(DSU, ComponentCount) {
	DSU dsu(5);
	ASSERT_EQ(dsu.components(), static_cast<std::size_t>(5));
	dsu.unite(1, 2);
	dsu.unite(2, 3);
	ASSERT_EQ(dsu.components(), static_cast<std::size_t>(3));
	dsu.unite(1, 3);
	ASSERT_EQ(dsu.components(), static_cast<std::size_t>(3));
}