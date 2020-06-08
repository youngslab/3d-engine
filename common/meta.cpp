#include <cassert>
#include <iostream>
#include <tuple>
#include <type_traits>

template <typename TypeList, typename T>
struct has : std::false_type {};

template <template <typename...> class TypeList, typename T, typename... Us>
struct has<TypeList<T, Us...>, T> : std::true_type {};

template <template <typename...> class TypeList, typename T, typename U,
          typename... Us>
struct has<TypeList<U, Us...>, T> : has<TypeList<Us...>, T> {};

template <typename TypeList, typename T>
inline constexpr bool has_v = has<TypeList, T>::value;

template <typename TypeList>
struct head;

template <template <typename...> class TypeList, typename T, typename... Ts>
struct head<TypeList<T, Ts...>> {
  using type = T;
};

template <typename TypeList>
using head_t = typename head<TypeList>::type;

template <typename TypeList>
struct tail;

template <template <typename...> class TypeList, typename T, typename... Ts>
struct tail<TypeList<T, Ts...>> {
  using type = TypeList<Ts...>;
};

template <typename TypeList>
using tail_t = typename tail<TypeList>::type;

template <typename TypeList, typename T>
struct insert;

template <template <typename...> class TypeList, typename T, typename... Us>
struct insert<TypeList<Us...>, T> {
  using type = TypeList<T, Us...>;
};

template <typename TypeList, typename T>
using insert_t = typename insert<TypeList, T>::type;

// pack
// list ++ a
// append

namespace detail {

template <typename TypeList, typename Enable = void>
struct _unique;

template <template <typename...> typename TypeList, typename T>
struct _unique<TypeList<T>> {
  using type = TypeList<T>;
};  //

template <template <typename...> typename TypeList, typename T, typename... Ts>
struct _unique<
    TypeList<T, Ts...>,
    std::enable_if_t<!has_v<TypeList<Ts...>, T> && sizeof...(Ts) != 0>> {
  using type = insert_t<typename _unique<TypeList<Ts...>>::type, T>;
};

template <template <typename...> typename TypeList, typename T, typename... Ts>
struct _unique<TypeList<T, Ts...>,
               std::enable_if_t<has_v<TypeList<Ts...>, T>>> {
  using type = typename _unique<TypeList<Ts...>>::type;
};

}  // namespace detail

template <typename TypeList>
struct unique {
  using type = typename detail::_unique<TypeList>::type;
};

template <typename TypeList>
using unique_t = typename unique<TypeList>::type;

int main() {
  std::cout << "tuple  : " << typeid(std::tuple<int, float>).name() << "\n";
  std::cout
      << "unique : "
      << typeid(
             detail::_unique<std::tuple<int, int, int, float, int, int>>::type)
             .name()
      << "\n";
  return 0;
}
