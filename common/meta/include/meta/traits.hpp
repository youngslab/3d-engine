#pragma once

#include <tuple>
#include <type_traits>

namespace meta {

struct nil {};

template <typename T>
struct is_type : public std::true_type {};

template <typename T>
constexpr inline bool is_type_v = is_type<T>::value;

template <typename Func, typename Enable = void>
struct has_value : std::false_type {};

template <typename Func>
struct has_value<Func, std::enable_if_t<is_type_v<decltype(Func::value)>>>
    : std::true_type {};

template <typename Func>
constexpr static bool has_value_v = has_value<Func>::value;

template <typename Func, typename Enable = void>
struct has_type : std::false_type {};

template <typename Func>
struct has_type<Func, std::enable_if_t<is_type_v<typename Func::type>>>
    : std::true_type {};

template <typename Func>
constexpr static bool has_type_v = has_type<Func>::value;

namespace detail {

template <typename Func, typename TypeList, typename Enable = void>
struct has_operator_ : std::false_type {};

template <typename Func, template <typename...> typename TypeList,
          typename... Args>
struct has_operator_<
    Func, TypeList<Args...>,
    std::enable_if_t<is_type_v<decltype(Func::template op<Args...>())>>>
    : std::true_type {};

}  // namespace detail

template <typename Func, typename... Args>
struct has_operator : public detail::has_operator_<Func, std::tuple<Args...>> {
};

template <typename Func, typename... Args>
constexpr static bool has_operator_v = has_operator<Func, Args...>::value;

template <typename T>
struct is_container : public std::false_type {};

template <template <typename...> typename Container, typename... Args>
struct is_container<Container<Args...>> : public std::true_type {};

template <typename T>
constexpr static bool is_container_v = is_container<T>::value;

}  // namespace meta
