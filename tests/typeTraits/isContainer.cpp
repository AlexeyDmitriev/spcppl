#include <spcppl/typeTraits/IsContainer.hpp>
#include <vector>
#include <string>

static_assert(!IsContainer<int>::value, "");
static_assert(IsContainer<std::vector<int>>::value, "");
static_assert(IsContainer<std::string>::value, "");
