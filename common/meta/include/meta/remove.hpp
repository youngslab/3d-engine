#pragma once

#include "pack.hpp"

namespace meta {

template <typename TypeList, typename T>
struct remove;

template <template <typename...> typename TypeList, typename U>
struct remove<TypeList<>, U> {
  using type = TypeList<>;
};

template <template <typename...> typename TypeList, typename T, typename... Ts,
          typename U>
struct remove<TypeList<T, Ts...>, U> {
  using type = pack_t<T, typename remove<TypeList<Ts...>, U>::type>;
};

template <template <typename...> typename TypeList, typename T, typename... Ts>
struct remove<TypeList<T, Ts...>, T> {
  using type = TypeList<Ts...>;
};

template <typename TypeList, typename T>
using remove_t = typename remove<TypeList, T>::type;

}  // namespace meta
