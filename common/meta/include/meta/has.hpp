#pragma once

#include <type_traits>

namespace meta {

template <typename TypeList, typename T>
struct has : std::false_type {};

template <template <typename...> class TypeList, typename T, typename... Us>
struct has<TypeList<T, Us...>, T> : std::true_type {};

template <template <typename...> class TypeList, typename T, typename U,
          typename... Us>
struct has<TypeList<U, Us...>, T> : has<TypeList<Us...>, T> {};

template <typename TypeList, typename T>
inline constexpr bool has_v = has<TypeList, T>::value;
}  // namespace meta
