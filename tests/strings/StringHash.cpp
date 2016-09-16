#include <gtest/gtest.h>
#include <spcppl/strings/hash/StringHash.hpp>
#include <spcppl/strings/hash/TwoIntsHasher.hpp>
#include <spcppl/strings/hash/OverflowHasher.hpp>

template <typename T>
struct StringHashTest : ::testing::Test {};

using Hashers = ::testing::Types<OverflowHasher, TwoIntsHasher>;
TYPED_TEST_CASE(StringHashTest, Hashers);

TYPED_TEST(StringHashTest, HasEqualHashForEqualStrings) {
	StringHash<TypeParam> hash("abacaba");
	EXPECT_EQ(hash.hash(0, 2), hash.hash(4, 6));
	EXPECT_EQ(hash.hash(2, 3), hash.hash(4, 5));
}

TYPED_TEST(StringHashTest, PrefixSuffixHash) {
	StringHash<TypeParam> hash("abacaba");
	EXPECT_EQ(hash.prefixHash(5), hash.hash(0, 5));
	EXPECT_EQ(hash.prefixHash(3), hash.suffixHash(4));
	EXPECT_EQ(hash.suffixHash(6), hash.hash(6, 7));
}

TYPED_TEST(StringHashTest, SmallDifferentStringHaveDifferentHash) {
	StringHash<TypeParam> hash("abacaba");
	EXPECT_NE(hash.hash(1, 3), hash.hash());
	EXPECT_NE(hash.hash(0, 1), hash.hash(3, 4));
	EXPECT_NE(hash.prefixHash(1), hash.prefixHash(2));
}

TYPED_TEST(StringHashTest, HashForEmptySubstringsAreEqual) {
	StringHash<TypeParam> hash("abacaba");
	EXPECT_EQ(hash.hash(3, 3), hash.hash(5, 5));
}

TYPED_TEST(StringHashTest, HashesInDifferentStringAreSame) {
	StringHash<TypeParam> abacaba("abacaba");
	StringHash<TypeParam> abra("abrackadabra");

	EXPECT_EQ(abacaba.hash(0, 2), abra.hash(0, 2));
	EXPECT_EQ(abacaba.hash(2, 4), abra.hash(3, 5));
	EXPECT_EQ(abacaba.hash(1, 2), abra.hash(9, 10));
}
