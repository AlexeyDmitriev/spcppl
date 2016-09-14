#include <gtest/gtest.h>
#include <spcppl/identity.hpp>

TEST(Identity, Integer) {
	 ASSERT_EQ(identity<int>(), 1);
}
