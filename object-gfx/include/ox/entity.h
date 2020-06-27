#include <meta/meta.hpp>
#include <variant>

namespace ox {

// less
class drawable {};
class shadable {};
class updatable {};
class inputable {};

// relation
struct aspect_relation {
  template <typename T>
  struct order;

  template <>
  struct order<drawable> {
    constexpr static int value = 1;
  };

  template <>
  struct order<shadable> {
    constexpr static int value = 2;
  };

  template <>
  struct order<updatable> {
    constexpr static int value = 3;
  };
  template <>
  struct order<inputable> {
    constexpr static int value = 4;
  };

  template <typename T>
  constexpr static int order_v = order<T>::value;

  template <typename T, typename U>
  constexpr static auto op()
      -> std::conditional_t<((order_v<T>) < (order_v<U>)), std::true_type,
                            std::false_type>;
};

template <typename... Ts>
struct component {};

template <typename... Ts>
struct make_component {
  using type = meta::sort_t<component<Ts...>, aspect_relation>;
};

template <typename... Ts>
using make_component_t = typename make_component<Ts...>::type;

using components_ =
    meta::subset_t<std::variant<>,
                   make_component_t<drawable, shadable, inputable, updatable>>;

struct make_shared_ptr {
  template <typename T>
  constexpr static auto op() -> std::shared_ptr<T>;
};
using components = meta::foreach_t<components_, make_shared_ptr>;

}  // namespace ox

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
