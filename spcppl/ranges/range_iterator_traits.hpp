#include <iterator>
#include <type_traits>

template <typename T>
using range_iterator_traits = std::iterator_traits<typename std::decay<decltype(std::declval<T>().begin())>::type>;
