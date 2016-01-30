#include <type_traits>

template <bool b, typename T = void>
using enable_if_t = typename std::enable_if<b, T>::type;