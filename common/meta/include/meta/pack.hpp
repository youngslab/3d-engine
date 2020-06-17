#pragma once

namespace meta {

template <typename T, typename U>
struct pack;

template <template <typename...> typename TypeList, typename... Ts, typename U>
struct pack<TypeList<Ts...>, U> {
  using type = TypeList<Ts..., U>;
};

template <template <typename...> typename TypeList, typename... Ts, typename U>
struct pack<U, TypeList<Ts...>> {
  using type = TypeList<U, Ts...>;
};

template <template <typename...> typename TypeList, typename... Ts,
          typename... Us>
struct pack<TypeList<Ts...>, TypeList<Us...>> {
  using type = TypeList<Ts..., Us...>;
};

template <typename T, typename U>
using pack_t = typename pack<T, U>::type;

}  // namespace meta
