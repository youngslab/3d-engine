#pragma once

#include <tuple>
#include "traits.hpp"

namespace meta {

namespace detail {

template <typename Func, typename TypeList, typename Eanble = void>
struct invoke_;

template <template <typename...> typename Func, typename... Ts,
          template <typename...> typename TypeList, typename... Args>
struct invoke_<Func<Ts...>, TypeList<Args...>,
               std::enable_if_t<has_type_v<Func<Ts...>>>> {
  using type = typename Func<Args...>::type;
};

template <template <typename...> typename Func, typename... Ts,
          template <typename...> typename TypeList, typename... Args>
struct invoke_<Func<Ts...>, TypeList<Args...>,
               std::enable_if_t<has_operator_v<Func<Ts...>, Args...>>> {
  using type = decltype(Func<Ts...>::template op<Args...>());
};
}  // namespace detail

template <typename Func, typename... Args>
class invoke : public detail::invoke_<Func, std::tuple<Args...>> {};

template <typename Func, typename... Args>
using invoke_t = typename invoke<Func, Args...>::type;

}  // namespace meta
