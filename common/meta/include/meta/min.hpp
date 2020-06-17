#pragma once

#include <type_traits>

namespace detail {

// TODO: change name to min_element. std::min vs. std::min_element
template <typename TypeList, typename Min, typename Comparer>
struct _min;

template <template <typename...> typename TypeList, typename T, typename Min,
          typename Comparer>
struct _min<TypeList<T>, Min, Comparer> {
  using type = std::conditional_t<Comparer::compare(T{}, Min{}), T, Min>;
};

// partail specailization
template <template <typename...> typename TypeList, typename T, typename... Ts,
          typename Min, typename Comparer>
struct _min<TypeList<T, Ts...>, Min, Comparer>
    : public _min<TypeList<Ts...>,
                  typename _min<TypeList<T>, Min, Comparer>::type, Comparer> {};

}  // namespace detail

template <typename TypeList, typename Comparer>
struct min;

template <template <typename...> typename TypeList, typename T, typename... Ts,
          typename Comparer>
struct min<TypeList<T, Ts...>, Comparer>
    : public detail::_min<TypeList<T, Ts...>, T, Comparer> {};

template <typename TypeList, typename Comparer>
using min_t = typename min<TypeList, Comparer>::type;

struct typesize_comparer {
  template <typename T, typename U>
  constexpr static auto compare(T, U) -> bool {
    return sizeof(T) < sizeof(U);
  }
};
