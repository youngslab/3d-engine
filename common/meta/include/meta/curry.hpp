#pragma once

#include "invoke.hpp"

namespace meta {

template <typename Func, typename... Ts>
struct lcurry {
  template <typename... Args>
  constexpr static auto op() -> invoke_t<Func, Ts..., Args...>;
};

template <typename Func, typename... Ts>
struct rcurry {
  template <typename... Args>
  constexpr static auto op() -> invoke_t<Func, Args..., Ts...>;
};

}  // namespace meta
