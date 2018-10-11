#include <spcppl/typeTraits/IsSaneInteger.hpp>
#include <cstdint>
#include <vector>

static_assert(IsSaneInteger<int>);
static_assert(IsSaneInteger<const int>);
static_assert(IsSaneInteger<int64_t>);

static_assert(!IsSaneInteger<double>);
static_assert(!IsSaneInteger<char>);
static_assert(!IsSaneInteger<const char>);
static_assert(!IsSaneInteger<std::vector<int>>);
