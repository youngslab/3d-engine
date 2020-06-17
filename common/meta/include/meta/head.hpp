#pragma once

namespace meta{

template <typename TypeList>
struct head;

template <template <typename...> class TypeList, typename T, typename... Ts>
struct head<TypeList<T, Ts...>> {
  using type = T;
};

template <typename TypeList>
using head_t = typename head<TypeList>::type;

}
