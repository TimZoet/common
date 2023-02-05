#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <type_traits>

//https://stackoverflow.com/questions/45249985/how-to-require-an-exact-function-signature-in-the-detection-idiom/45250180#45250180

namespace detail {
    template <class Default, class AlwaysVoid,
        template<class...> class Op, class... Args>
    struct detector {
        using value_t = std::false_type;
        using type = Default;
    };

    template <class Default, template<class...> class Op, class... Args>
    struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
        using value_t = std::true_type;
        using type = Op<Args...>;
    };

} // namespace detail

struct nonesuch {
    nonesuch() = delete;
    ~nonesuch() = delete;
    nonesuch(nonesuch const&) = delete;
    void operator=(nonesuch const&) = delete;
};

template <template<class...> class Op, class... Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template <template<class...> class Op, class... Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template<class...> class Op, class... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

/*
Usage example.

struct A
{
    int x;
};

struct test
{
    using x = float;

    A foo(int x, int y) { A a; a.x = x + y; return a; }
};

template <typename T, typename ...Ts>
using foo_type = decltype(std::declval<T>().foo(std::declval<Ts>()...));

template<typename T, typename Ret, typename ...Args>
using has_foo_full = std::conjunction<is_detected<foo_type, T, Args...>, std::is_same<Ret, detected_t<foo_type, T, Args...>>>; // has arguments && has return type

static_assert(has_foo_full<test, A, int, int>::value, "error");

*/
