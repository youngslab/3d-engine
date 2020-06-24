#pragma once

namespace meta {

template <typename Container, typename TypeList>
struct subset;

template <template <typename...> typename TypeList>
struct subset<TypeList<>> {
  using type = TypeList<>;
}

template <typename<typename...> Container,
          template <typename...> typename TypeList>
struct subset<Container<>, TypeList<>> {
  using type = Container<TypeList<>>;
}

template <typename<typename...> Container,
          template <typename...> typename TypeList, TypeList<>>
struct subset<Container<>, TypeList<>> {
  using type = Container<TypeList<>>;
}

}  // namespace meta

// example
// make_variant<x,y,z>
// struct foo : public component<shadable, updatable>
// foo<a,b,c> -> std::variant<foo<a>, foo<b>, foo<c>, foo<a,b>, foo<a,c>,
// foo<b,c>, foo<a,b,c>> subset_t<std::variant<>, sort_t<unique_t<x>>>
//
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
}
