#pragma onoce

#include <iostream>

namespace meta {
template <typename TypeList, typename T, int N = 0>
struct select;

template <template <typename...> typename TypeList, typename T, typename... Ts,
          typename U, int N>
struct select<TypeList<T, Ts...>, U, N>
    : public select<TypeList<Ts...>, U, N + 1> {};

template <template <typename...> typename TypeList, typename T, typename... Ts,
          int N>
struct select<TypeList<T, Ts...>, T, N> {
  constexpr static int value = N;
  using type = TypeList<T, Ts...>;
};

template <typename TypeList, typename U>
inline constexpr static int select_v = select<TypeList, U>::value;
}  // namespace meta
