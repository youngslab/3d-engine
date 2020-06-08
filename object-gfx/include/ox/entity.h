
#include <type_traite>

namespace ox {

template<typename TypeList, typename T>
struct has : std::false_type {};

template<template<typename...> class TypeList, typename T, typename... Us>
struct has <TypeList<T, Us...>, T> : std::true_type { };

template<template<typename...> class TypeList, typename T, typename U, typename... Us>
struct has <TypeList<U, Us...>, T> : has<TypeList<Us...>, T> {};

// 2. min
// 3. compare

template<typename T>
struct has_order {
	static constexpr bool value = has_order;
}


template<typename T, typename U, typename enabled = is_defined<T> && is_defined<U> >
auto compare(T, U) -> bool{
	return order<T>() > order<U>();
}

template<typename T, typename U>
class _compare {
  using type = std::if
};
}

template<template<class typelist>, typename... Ts>
class min {
 
}




// option to have its classes.
class enum PROPERTY {
  OX_SHADABLE,
  OX_PROGRAMABLE,
  OX_COMPONENT_DRAWABLE,
};

//
class drawable {
public:
  virtual ~drawable() {}
  virtual auto draw() = 0;
};

class programable : ogl::program {
public:
  virtual ~programable() {}
  // ogl::prgoram define set(name, value) interfaces.
}

class shadable {
public:
  virtual ~shadable(){};
  virtual auto config(programable &p);
};

template <typename... Ts> class component : public Ts... {
  virtual ~component() {}
}

// drawable, programable, combination<shadable, updatable>

// 5, 4,3,2,1
1,
    2, 3 = > {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {
  1, 2, 3
}

// 2 ^ n - 1
8->2 ^ 8 - 1

	   class drawable {};
class shadable {};
class updatable {};
class inputable {};

// Aspect
enum class aspect {
  drawable
}

// Combination of types. But one for each aspects.

using comp = std::variant<std::shared_ptr<component<drawable>>,
			  std::shared_ptr<component<programable>>,
			  std::shared_ptr<shadable>, std::shared_ptr<updatable>,
			  std::shared_ptr<compositable<shadable, updatable>>>;

class entity {
public:
  auto add(component const &c) { cs_s.push_back(c); }

private:
  std::vector<component> cs_;
};
} // namespace ox

// Example
/*
 * auto entity;
 * render(entity);
 * render(entity->mesh, entity->program, components..., this->camera); // what
 * if element doesn't need camear.. like sprite? only entity knows..
 * render(verticies, program, shadables...)
 * frame-graph
 * entity.render(framegraph);
 *
 * */
