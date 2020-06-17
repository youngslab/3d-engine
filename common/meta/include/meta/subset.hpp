#pragma once

namespace meta{


// Operate can't be a template. The Metafunction
template<typename TypeList, typename Op>
struct foreach;


template<template <typename...> typename TypeList, typename T, typename... Ts, typename Op>
struct foreach<TypeList<T, Ts...>, Op> {
  // uusing type = pack_t<decltype(std::declval<Op>()(std::declval<T>())), typename foreach<TypeList<Ts...>, Op>::type>;
	using head_ = decltype(Op::operate<T>());
  using type = pack_t<decltype(std::declval<Op>()(std::declval<T>())), typename foreach<TypeList<Ts...>, Op>::type>;
}


template<typename Container, typename TypeList>
struct subset;

template<template <typename...> typename TypeList>
struct subset<TypeList<>> {
  using type = TypeList<>;
}

template<typename <typename...> Container, template <typename...> typename TypeList>
struct subset<Container<>, TypeList<>> {
  using type = Container<TypeList<>>;
}

template<typename <typename...> Container, template <typename...> typename TypeList, TypeList<>>
struct subset<Container<>, TypeList<>> {
  using type = Container<TypeList<>>;
}

}


// example
// make_variant<x,y,z>
// struct foo : public component<shadable, updatable>
// foo<a,b,c> -> std::variant<foo<a>, foo<b>, foo<c>, foo<a,b>, foo<a,c>, foo<b,c>, foo<a,b,c>>
// subset_t<std::variant<>, sort_t<unique_t<x>>>
