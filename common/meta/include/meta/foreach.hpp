#pragma once

#include "pack.hpp"

namespace meta{

template<typename TypeList, typename UnaryOp>
struct foreach ;


template<template <typename...> typename TypeList, typename Op>
struct foreach<TypeList<>, Op> {
  using type = TypeList<>;
};

template<template <typename...> typename TypeList, typename T, typename... Ts, typename Op>
struct foreach<TypeList<T, Ts...>, Op> {
  using res_ = decltype(Op::op(std::declval<T>()));
  using type = pack_t<res_, typename foreach<TypeList<Ts...>, Op>::type>;
};

}
