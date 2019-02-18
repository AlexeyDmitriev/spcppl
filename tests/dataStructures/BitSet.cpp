#include <gtest/gtest.h>
#include <spcppl/dataStructures/BitSet.hpp>
#include <spcppl/make_constant.hpp>
#include "tests/operator_size.hpp"

using BS = BitSet<std::integral_constant<std::size_t, 5>>;
using LongBS = BitSet<std::integral_constant<std::size_t, 100>>;

TEST(BitSetTest, CreatedEmptyByDefault) {
	BS bs;
	EXPECT_TRUE(bs.empty());
}

TEST(BitSetTest, EqulitisBitwise) {
	BS lhs;
	BS rhs;

	EXPECT_EQ(lhs, rhs);

	lhs.set(3);
	EXPECT_NE(lhs, rhs);

	rhs.set(3);
	EXPECT_EQ(lhs, rhs);
}

TEST(BitSetTest, CreatingFromIndiciesFillCorrectIndices) {
	BS bs = BS::fromIndices({1, 4});
	EXPECT_FALSE(bs.get(0));
	EXPECT_TRUE(bs.get(1));
	EXPECT_FALSE(bs.get(2));
	EXPECT_FALSE(bs.get(3));
	EXPECT_TRUE(bs.get(4));
}

TEST(BitSetTest, EmptyChecksIfThereAreBits) {
	BS bs1 = BS::fromIndices({});
	EXPECT_TRUE(bs1.empty());

	BS bs2 = BS::fromIndices({1});
	EXPECT_FALSE(bs2.empty());
}

TEST(BitSetTest, OrderDoesntMatterOnCreation) {
	BS bs1 = BS::fromIndices({2, 0, 3});
	BS bs2 = BS::fromIndices({2, 3, 0});

	EXPECT_EQ(bs1, bs2);
}


TEST(BitSetTest, XorWorks) {
	BS lhs = BS::fromIndices({0, 1});
	BS rhs = BS::fromIndices({0, 2});

	EXPECT_EQ(lhs ^ rhs, BS::fromIndices({1, 2}));
}

TEST(BitSetTest, AndWorks) {
	BS lhs = BS::fromIndices({0, 1});
	BS rhs = BS::fromIndices({0, 2});
	EXPECT_EQ(lhs & rhs, BS::fromIndices({0}));
}

TEST(BitSetTest, OrWorks) {
	BS lhs = BS::fromIndices({0, 1});
	BS rhs = BS::fromIndices({0, 2});
	EXPECT_EQ(lhs | rhs, BS::fromIndices({0, 1, 2}));
}

TEST(BitSetTest, NegatingWorks) {
	BS bs = BS::fromIndices({1, 4});
	EXPECT_EQ(~bs, BS::fromIndices({0, 2, 3}));
	EXPECT_EQ(~BS::fromIndices({1, 4}), BS::fromIndices({0, 2, 3}));
}

TEST(BitSetTest, CanAddBitBySetting) {
	BS bs = BS::fromIndices({0, 1});
	bs.set(2);
	EXPECT_EQ(bs, BS::fromIndices({0, 1, 2}));
}

TEST(BitSetTest, CanAddBitBySettingTrue) {
	BS bs = BS::fromIndices({0, 1});
	bs.set(2, true);
	EXPECT_EQ(bs, BS::fromIndices({0, 1, 2}));
}

TEST(BitSetTest, CanRemoveBitByClearing) {
	BS bs = BS::fromIndices({0, 1});
	bs.clear(0);
	EXPECT_EQ(bs, BS::fromIndices({1}));
}

TEST(BitSetTest, CanRemoveBitBySettingFalse) {
	BS bs = BS::fromIndices({0, 1});
	bs.set(0, false);
	EXPECT_EQ(bs, BS::fromIndices({1}));
}

TEST(BitSetTest, RemovingRemovedBitDoesntChangeAnything) {
	BS bs = BS::fromIndices({0, 1});
	BS changed = bs;
	changed.clear(2);
	EXPECT_EQ(bs, changed);

	changed.set(2, false);
	EXPECT_EQ(bs, changed);
}

TEST(BitSetTest, AddingAddedBitDoesntChangeAnything) {
	BS bs = BS::fromIndices({0, 1});
	BS changed = bs;
	changed.set(0);
	EXPECT_EQ(bs, changed);

	changed.set(0, true);
	EXPECT_EQ(bs, changed);
}

TEST(BitSetTest, FlipChangeFalseToTrueAndViceVersa) {
	BS bs = BS::fromIndices({0, 1});
	EXPECT_TRUE(bs.get(1));
	EXPECT_FALSE(bs.get(3));

	bs.flip(1);
	bs.flip(3);

	EXPECT_FALSE(bs.get(1));
	EXPECT_TRUE(bs.get(3));

	EXPECT_EQ(bs, BS::fromIndices({0, 3}));
}

TEST(BitSetTest, CountReturnsNumberOfBits) {
	EXPECT_EQ(BS().count(), 0_size);
	EXPECT_EQ(BS::fromIndices({1, 4}).count(), 2_size);
	EXPECT_EQ(BS::fromIndices({0, 1, 2, 3, 4}).count(), 5_size);
	EXPECT_EQ(BS::fromIndices({4}).count(), 1_size);
}

TEST(BitSetTest, AssingXorWorks) {
	BS lhs = BS::fromIndices({0, 1});
	BS rhs = BS::fromIndices({0, 2});

	lhs ^= rhs;

	EXPECT_EQ(lhs, BS::fromIndices({1, 2}));
}

TEST(BitSetTest, AssingOrWorks) {
	BS lhs = BS::fromIndices({0, 1});
	BS rhs = BS::fromIndices({0, 2});

	lhs |= rhs;

	EXPECT_EQ(lhs, BS::fromIndices({0, 1, 2}));
}


TEST(BitSetTest, AssingAndWorks) {
	BS lhs = BS::fromIndices({0, 1});
	BS rhs = BS::fromIndices({0, 2});

	lhs &= rhs;

	EXPECT_EQ(lhs, BS::fromIndices({0}));
}

TEST(BitSetTest, LeastBitWorks) {
	EXPECT_EQ(BS::fromIndices({0, 3}).leastBit(), 0_size);
	EXPECT_EQ(BS::fromIndices({4, 1}).leastBit(), 1_size);
	EXPECT_EQ(BS::fromIndices({4}).leastBit(), 4_size);
}

TEST(BitSetTest, LeastBitForEmptyIsSize) {
	EXPECT_EQ(BS().leastBit(), 5_size);
}

TEST(BitSetTest, LeastBitWorksForLongBitSet) {
	EXPECT_EQ(LongBS().leastBit(), 100_size);
	EXPECT_EQ(LongBS::fromIndices({7, 23, 89}).leastBit(), 7_size);
	EXPECT_EQ(LongBS::fromIndices({56, 99}).leastBit(), 56_size);
	EXPECT_EQ(LongBS::fromIndices({32}).leastBit(), 32_size);
	EXPECT_EQ(LongBS::fromIndices({99}).leastBit(), 99_size);
}

TEST(BitSetTest, ShiftingRightWorks) {
	EXPECT_EQ(BS::fromIndices({2, 3}) >> 1, BS::fromIndices({1, 2}));
}

TEST(BitSetTest, ShiftingRightRemovesBits) {
	EXPECT_EQ(BS::fromIndices({1, 3}) >> 2, BS::fromIndices({1}));
}

TEST(BitSetTest, CanShiftRightForFullLength) {
	EXPECT_EQ(BS::fromIndices({1, 4}) >> 5, BS());
}

TEST(BitSetTest, ShiftingLeftWorks) {
	EXPECT_EQ(BS::fromIndices({2, 3}) << 1, BS::fromIndices({3, 4}));
}

TEST(BitSetTest, ShiftingLeftRemovesBits) {
	EXPECT_EQ(BS::fromIndices({1, 3}) << 3, BS::fromIndices({4}));
}

TEST(BitSetTest, CanShiftLeftForFullLength) {
	EXPECT_EQ(BS::fromIndices({1, 4}) << 5, BS());
}

TEST(BitSetTest, ShiftingLongBitsetAlsoWork) {
	EXPECT_EQ(LongBS::fromIndices({0, 31, 70}) << 48, LongBS::fromIndices({48, 79}));
	EXPECT_EQ(LongBS::fromIndices({98}) << 1, LongBS::fromIndices({99}));

	EXPECT_EQ(LongBS::fromIndices({5, 48, 64}) >> 48, LongBS::fromIndices({0, 16}));
	EXPECT_EQ(LongBS::fromIndices({1}) >> 1, LongBS::fromIndices({0}));
	EXPECT_EQ(LongBS::fromIndices({1}) >> 2, LongBS());
}
namespace {
MAKE_CONSTANT(N, size_t);
}
TEST(BitSetTest, CanChangeSizeInRuntime) {
	using BS = BitSet<N>;
	{
		N::value = 3;
		EXPECT_TRUE((BS::fromIndices({0}) << 3).empty());
	}
	{
		N::value = 5;
		EXPECT_FALSE((BS::fromIndices({0}) << 3).empty());
	}
}
