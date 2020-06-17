#pragma once

#include "min.hpp"
#include "remove.hpp"

namespace meta {

template <typename TypeList, typename Compare>
struct sort {
  using min_ = min_t<TypeList, Compare>;
  using type = pack_t<min_, remove_t<TypeList, min_>>;
};

template <template <typename...> typename TypeList, typename Compare>
struct sort<TypeList<>, Compare> {
  using type = TypeList<>;
};

template <typename TypeList, typename Compare>
using sort_t = typename sort<TypeList, Compare>::type;

}  // namespace meta
