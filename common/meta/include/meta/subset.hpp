#pragma once

#include "foreach.hpp"
#include "pack.hpp"

namespace meta {

template <typename Container, typename TypeList>
struct subset;

template <template <typename...> typename Container,
          template <typename...> typename TypeList>
struct subset<Container<>, TypeList<>> {
  using type = Container<TypeList<>>;
};

template <template <typename...> typename Container,
          template <typename...> typename TypeList, typename T>
struct subset<Container<>, TypeList<T>> {
  using type = Container<TypeList<T>, TypeList<>>;
};

template <template <typename...> typename Container,
          template <typename...> typename TypeList, typename T, typename... Ts>
struct subset<Container<>, TypeList<T, Ts...>> {
  using sub_ = typename subset<Container<>, TypeList<Ts...>>::type;
  using inserter = rcurry<push_front<nil, nil>, T>;
  using appended = foreach_t<sub_, inserter>;
  using type = pack_t<appended, sub_>;
};

template <typename Container, typename TypeList>
using subset_t = typename subset<Container, TypeList>::type;

}  // namespace meta

// example
// make_variant<x,y,z>
// struct foo : public component<shadable, updatable>
// foo<a,b,c> -> std::variant<foo<a>, foo<b>, foo<c>, foo<a,b>, foo<a,c>,
// foo<b,c>, foo<a,b,c>> subset_t<std::variant<>, sort_t<unique_t<x>>>
// foo<c> -> subset_t<std::variant<>, foo<c>> ->
// 1) std::tuple<a,b> -> std::tuple<std::tuple<a,b>, std:tuple<a>
// std::tuple<b>,std::typle<>>;
//
/*
 *
 *
subset_t<TypeList<T, Ts...>>


TypeList<T> +  // head

subset_t<TypeList<Ts...>>
std::tuple<> + foreach<subset_t<tail_t<Ts>>, curry_r<push_front<meta::nil,
meta::nil>, T>
*/
//}
