#pragma once

namespace meta {
template <typename TypeList, typename T>
struct push_front;

template <>
struct push_front<nil, nil> {
  using type = nil;
};

template <template <typename...> typename TypeList, typename... Ts, typename U>
struct push_front<TypeList<Ts...>, U> {
  using type = TypeList<U, Ts...>;
};
}  // namespace meta
