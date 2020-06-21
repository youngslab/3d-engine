#pragma once

namespace meta{


// com<a, b, c>

namespace detail{

template<typename T, typename Container=std::tuple<>>
struct add_{
	template<typename U>
	constexpr static op(U)-> Container<T, U>;
}


// currying
template <typename T>
struct packer {
	template<typename U>
	constexpr static auto op() -> pack_t<T, U>;
}


template<


// metafunction : func_t<arg>
//

// currying
template<typename MetaFunc, typename 
struct curried{


};

foreach<tail<Xs>, packer<U> >


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
