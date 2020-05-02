#pragma once

namespace ogl {

template <typename Vertices, typename Program, typename... Shadables>
auto render(Vertices const &vs, Program &program, Shadables &&... shadables)
    -> bool {
  bind(program);

  auto success = (config(program, std::forward<Shadables>(shadables)) | ...);

  if (success) {
    draw(vs);
  }

  unbind(program);
  return success;
}

template <typename Vertices, typename Program, typename Shadables>
auto render(Vertices const &vs, Program &program,
	    std::vector<Shadables const &> const &shadables) -> bool {
  bind(program);

  auto success = true;
  for (auto &s : shadables) {
    success &= config(program, *s);
  }

  if (success) {
    std::cout << "darw\n";
    draw(vs);
  } else {
    std::cout << "darw -failed\n";
  }

  unbind(program);
  return success;
}

} // namespace ogl
