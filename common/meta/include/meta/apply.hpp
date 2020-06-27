#pragma once
#include <type_traits>
#include "traits.hpp"

namespace meta {

template <typename Func, typename TypeList, typename Enable = void>
struct apply;

// when passing metafunction. we could fill the param with nil
// ex) apply<uinque<nil>, std::tuple<int, bool, int, char>> -> std::tuple<int,
// bool, int, char>
template <template <typename...> typename Func, typename... Args,
          template <typename...> typename TypeList, typename... Ts>
struct apply<Func<Args...>, TypeList<Ts...>,
             std::enable_if_t<has_type_v<Func<Args...>>>> {
  using type = typename Func<Ts...>::type;
};

template <template <typename> typename Func, typename Arg, typename T>
struct apply<Func<Arg>, T,
             std::enable_if_t<(has_type_v<Func<Arg>> && !is_container_v<T>)>> {
  using type = typename Func<T>::type;
};

template <typename Func, typename TypeList>
using apply_t = typename apply<Func, TypeList>::type;

}  // namespace meta
