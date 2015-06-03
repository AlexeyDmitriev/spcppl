#include <vector>
/*
 * Uses unneeded first arg so that it's possible to determine return value
 *
 * it could be done in other ways
 * http://stackoverflow.com/q/29995642/768110
 *
 * But this one better works in CLion (don't shows not existing errors)
 *
 * TODO: Consider changing it back once https://youtrack.jetbrains.com/issue/CPP-3340 is fixed
 */
namespace impl {
    struct adl_helper {
    };

    template <class T, class Adl>
    std::vector<T> make_vector(Adl, size_t size, const T& value) {
	    return std::vector<T>(size, value);
    }

    template <
		    class T, class Adl, class... Args,
		    class R_T=decltype(
		    make_vector<T>(Adl{}, std::declval<Args>()...)
		    ),
		    class R=std::vector<R_T>
    >
    R make_vector(Adl, size_t first, Args... sizes) {
	    auto inner = make_vector<T>(Adl{}, std::forward<Args>(sizes)...);
	    return R(first, inner);
    }
}

template <
		class T, class... Args,
		class R=decltype(impl::make_vector<T>(impl::adl_helper{}, std::declval<Args>()...))
>
R make_vector(Args... args) {
	return impl::make_vector<T>(impl::adl_helper{}, std::forward<Args>(args)...);
}
