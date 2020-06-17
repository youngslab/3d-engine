#pragma once

namespace meta{

template <typename TypeList>
struct tail;

template <template <typename...> class TypeList, typename T, typename... Ts>
struct tail<TypeList<T, Ts...>> {
  using type = TypeList<Ts...>;
};

template <typename TypeList>
using tail_t = typename tail<TypeList>::type;
}
