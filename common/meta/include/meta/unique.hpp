#pragma once

#include "has.hpp"
#include "pack.hpp"

namespace meta {

namespace detail {

template <typename TypeList, typename Enable = void>
struct _unique;

template <template <typename...> typename TypeList, typename T>
struct _unique<TypeList<T>> {
  using type = TypeList<T>;
};  //

template <template <typename...> typename TypeList, typename T, typename... Ts>
struct _unique<
    TypeList<T, Ts...>,
    std::enable_if_t<!has_v<TypeList<Ts...>, T> && sizeof...(Ts) != 0>> {
  // using type = insert_t<typename _unique<TypeList<Ts...>>::type, T>;
	 using type = pack_t<typename _unique<TypeList<Ts...>>::type, T>;
};

template <template <typename...> typename TypeList, typename T, typename... Ts>
struct _unique<TypeList<T, Ts...>,
               std::enable_if_t<has_v<TypeList<Ts...>, T>>> {
  using type = typename _unique<TypeList<Ts...>>::type;
};

}  // namespace detail

template <typename TypeList>
struct unique {
  using type = typename detail::_unique<TypeList>::type;
};

template <typename TypeList>
using unique_t = typename unique<TypeList>::type;
}
