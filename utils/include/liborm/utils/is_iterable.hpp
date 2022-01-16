#ifndef LIBORM_UTILS_IS_ITERABLE_HPP
#define LIBORM_UTILS_IS_ITERABLE_HPP

#include <type_traits>

// Variable template that checks if a type has begin() and end() member functions
// documentation: https://en.cppreference.com/w/cpp/types/void_t
template <typename, typename = void>
constexpr bool is_iterable{};
 
template <typename T>
constexpr bool is_iterable<
    T,
    std::void_t< decltype(std::declval<T>().begin()),
                 decltype(std::declval<T>().end())
    >
> = true;

#endif