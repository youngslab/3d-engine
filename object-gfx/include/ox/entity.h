
#include <type_traite>

namespace ox {


// less
class drawable {};
class shadable {};
class updatable {};
class inputable {};

// relation
struct aspect_relation{
	auto order(drawable) { return 0;}
	auto order(shadable) { return 1;}
	auto order(updatable) { return 2;}
	auto order(inputable) { return 3;}

	template<typename T, typename U>
  auto compare(T, U) -> bool{
	  return order(std::declval<T>()) < order(std::declval<U>());
	}
};


using component = std::variant<std::shared_ptr<drawable>, 


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
