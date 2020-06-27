#include <cassert>
#include <iostream>
#include <meta/meta.hpp>
#include <tuple>
#include <type_traits>
#include <variant>

auto test_min() -> void;
auto test_select() -> void;
auto test_pack() -> void;
auto test_remove() -> void;
auto test_sort() -> void;
auto test_foreach() -> void;
auto test_apply() -> void;
auto test_invoke() -> void;
auto test_curry() -> void;
auto test_subset() -> void;

int main() {
  test_invoke();
  test_apply();
  test_foreach();
  test_min();
  test_select();
  test_pack();
  test_remove();
  test_sort();
  test_curry();
  test_subset();
  return 0;
}

auto test_subset() -> void {
  auto res = std::is_same_v<meta::subset_t<std::variant<>, std::tuple<int>>,
                            std::variant<std::tuple<int>, std::tuple<>>>;

  assert(res);

  res = std::is_same_v<meta::subset_t<std::variant<>, std::tuple<int, char>>,
                       std::variant<std::tuple<int, char>, std::tuple<int>,
                                    std::tuple<char>, std::tuple<>>>;

  assert(res);

  // subsets of<int, char, float>
  res = std::is_same_v<
      meta::subset_t<std::variant<>, std::tuple<int, char, float>>,
      std::variant<std::tuple<int, char, float>, std::tuple<int, char>,
                   std::tuple<int, float>, std::tuple<int>,
                   std::tuple<char, float>, std::tuple<char>, std::tuple<float>,
                   std::tuple<>>>;

  // assert
  assert(res);
}

// curry
auto test_curry() -> void {
  using int_inserter =
      meta::rcurry<meta::push_front<meta::nil, meta::nil>, int>;

  auto res = std::is_same_v<meta::invoke_t<int_inserter, std::tuple<char>>,
                            std::tuple<int, char>>;
  assert(res);

  res = std::is_same_v<meta::invoke_t<int_inserter, std::tuple<bool, char>>,
                       std::tuple<int, bool, char>>;
  assert(res);
}

auto test_apply() -> void {
  // using a = meta::apply_t<meta::unique<meta::nil>, std::tuple<int, char,
  // int>>;
}

template <typename T, typename U>
struct convert {
  template <typename K,
            typename Enable = std::enable_if_t<std::is_same_v<T, K>>>
  constexpr static auto op(K) -> U;

  template <typename K,
            typename Enable = std::enable_if_t<!std::is_same_v<T, K>>>
  constexpr static auto op(K) -> K;

  template <typename K,
            typename Enable = std::enable_if_t<std::is_same_v<T, K>>>
  constexpr static auto op() -> U;

  template <typename K,
            typename Enable = std::enable_if_t<!std::is_same_v<T, K>>>
  constexpr static auto op() -> K;
};

auto test_invoke() -> void {
  auto res = std::is_same_v<
      meta::invoke_t<meta::unique<meta::nil>, std::tuple<int, char, int>>,
      std::tuple<int, char>>;
  assert(res);

  res = meta::has_operator_v<meta::unique<meta::nil>, int>;
  assert(!res);

  res = meta::has_operator_v<convert<int, char>, int>;
  assert(res);

  res = meta::has_type_v<convert<int, char>>;
  assert(!res);
}

auto test_foreach() -> void {
  auto res = std::is_same_v<
      meta::foreach<std::tuple<int, char>, convert<int, char>>::type,
      std::tuple<char, char>>;

  assert(res);

  res = std::is_same_v<
      meta::foreach<std::tuple<int, int>, convert<int, char>>::type,
      std::tuple<char, char>>;
  assert(res);

  res = std::is_same_v<
      meta::foreach<std::tuple<char, char>, convert<int, char>>::type,
      std::tuple<char, char>>;
  assert(res);
}
auto test_sort() -> void {
  auto res = std::is_same_v<
      meta::sort_t<std::tuple<int, char>, meta::typesize_comparer>,
      std::tuple<char, int>>;
  assert(res);

  res = std::is_same_v<
      meta::sort_t<std::tuple<int, float, char>, meta::typesize_comparer>,
      std::tuple<char, int, float>>;
  assert(res);

  res = std::is_same_v<meta::sort_t<std::tuple<>, meta::typesize_comparer>,
                       std::tuple<>>;
  assert(res);
}
auto test_remove() -> void {
  // remove last element
  auto res = std::is_same_v<meta::remove_t<std::tuple<int, char>, char>,
                            std::tuple<int>>;
  assert(res);

  // remove first element
  res = std::is_same_v<meta::remove_t<std::tuple<int, char>, int>,
                       std::tuple<char>>;
  assert(res);

  // remove an non-element
  res = std::is_same_v<meta::remove_t<std::tuple<int, char>, float>,
                       std::tuple<int, char>>;
  assert(res);
}

auto test_pack() -> void {
  auto res = std::is_same_v<meta::pack_t<std::tuple<int>, char>,
                            std::tuple<int, char>>;
  assert(res);
  res = std::is_same_v<meta::pack_t<char, std::tuple<int>>,
                       std::tuple<char, int>>;
  assert(res);

  res = std::is_same_v<meta::pack_t<char, std::tuple<int>>, std::tuple<int>>;
  assert(!res);

  // union
  res = std::is_same_v<meta::pack_t<std::tuple<char>, std::tuple<int>>,
                       std::tuple<char, int>>;
  assert(res);
}

auto test_select() -> void {
  auto res = meta::select_v<std::tuple<int, double, int, int, char>, char>;
  assert(res == 4);
  res = meta::select_v<std::tuple<int, double, int, int, char>, int>;
  assert(res == 0);
}

auto test_min() -> void {
  std::cout << "min: "
            << typeid(
                   meta::min_t<std::tuple<int, float>, meta::typesize_comparer>)
                   .name()
            << "\n";
  struct float2 {
    float a, b;
  };
  std::cout << "min: "
            << typeid(meta::min_t<std::tuple<int, float, float2>,
                                  meta::typesize_comparer>)
                   .name()
            << "\n";
  std::cout << "min: "
            << typeid(meta::min_t<std::tuple<int, float, char, float2>,
                                  meta::typesize_comparer>)
                   .name()
            << "\n";
}
auto test_unqiue() {
  std::cout << "tuple  : " << typeid(std::tuple<int, float>).name() << "\n";
  std::cout
      << "unique : "
      << typeid(meta::unique<std::tuple<int, int, int, float, int, int>>::type)
             .name()
      << "\n";
}
