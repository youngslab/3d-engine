
#include <cassert>
#include <iostream>
#include <tuple>
#include <type_traits>

#include <meta/meta.hpp>

auto test_min() -> void;
auto test_select() -> void;
auto test_pack() -> void;
auto test_remove() -> void;
auto test_sort() -> void;
auto test_foreach()-> void;

int main() { 
	test_foreach();
	//test_min();
	//test_select();
	//test_pack();
	//test_remove();
	//test_sort();
	return 0; 
}

template<typename U, typename Convert>
struct convert{
  using type = decltype(Convert::op(std::declval<U>()));
};


template <typename T, typename U>
struct converter{
	template<typename K, typename Enable = std::enable_if_t<std::is_same_v<T,K>>>
	constexpr static auto op(K) -> U;
	
	template<typename K, typename Enable = std::enable_if_t<!std::is_same_v<T,K>>>
	constexpr static auto op(K) -> K;
};

auto test_foreach()-> void {
  auto res =
      std::is_same_v<meta::foreach<std::tuple<int, char>, converter<int, char>>::type,
                     std::tuple<char, char>>;

	assert(res);

  res =
      std::is_same_v<meta::foreach<std::tuple<int, int>, converter<int, char>>::type,
                     std::tuple<char, char>>;
	assert(res);
  
	res =
      std::is_same_v<meta::foreach<std::tuple<char, char>, converter<int, char>>::type,
                     std::tuple<char, char>>;
	assert(res);
}
auto test_sort() -> void {
  auto res =
      std::is_same_v<meta::sort_t<std::tuple<int, char>, typesize_comparer>,
                     std::tuple<char, int>>;
  assert(res);

  res = std::is_same_v<
      meta::sort_t<std::tuple<int, float, char>, typesize_comparer>,
      std::tuple<char, int, float>>;
  assert(res);

  res = std::is_same_v<meta::sort_t<std::tuple<>, typesize_comparer>,
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
            << typeid(min_t<std::tuple<int, float>, typesize_comparer>).name()
            << "\n";
  struct float2 {
    float a, b;
  };
  std::cout
      << "min: "
      << typeid(min_t<std::tuple<int, float, float2>, typesize_comparer>).name()
      << "\n";
  std::cout
      << "min: "
      << typeid(min_t<std::tuple<int, float, char, float2>, typesize_comparer>)
             .name()
      << "\n";
}
auto test_unqiue() {
  std::cout << "tuple  : " << typeid(std::tuple<int, float>).name() << "\n";
  std::cout
      << "unique : "
      << typeid(
             meta::unique<std::tuple<int, int, int, float, int, int>>::type)
             .name()
      << "\n";
}
