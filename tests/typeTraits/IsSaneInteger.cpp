#include <spcppl/typeTraits/IsSaneInteger.hpp>
#include <cstdint>
#include <vector>

static_assert(IsSaneInteger<int>::value);
static_assert(IsSaneInteger<const int>::value);
static_assert(IsSaneInteger<int64_t>::value);

static_assert(!IsSaneInteger<double>::value);
static_assert(!IsSaneInteger<char>::value);
static_assert(!IsSaneInteger<const char>::value);
static_assert(!IsSaneInteger<std::vector<int>>::value);
