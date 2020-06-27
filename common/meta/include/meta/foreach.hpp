#pragma once

#include "invoke.hpp"
#include "push.hpp"

namespace meta {

template <typename TypeList, typename UnaryOp, typename Enable = void>
struct foreach;

template <template <typename...> typename TypeList, typename Op>
struct foreach<TypeList<>, Op> {
  using type = TypeList<>;
};

template <template <typename...> typename TypeList, typename T, typename... Ts,
          typename Op>
struct foreach<TypeList<T, Ts...>, Op> {
  // apply function to its first parameter
  using res_ = invoke_t<Op, T>;
  using type = push_front_t<typename foreach<TypeList<Ts...>, Op>::type, res_>;
};

template <typename TypeList, typename UnaryOp>
using foreach_t = typename foreach<TypeList, UnaryOp>::type;

}  // namespace meta
