#pragma once

namespace oen {
class textured {
public:
  textured(ogl::texture t, GLuint uint) {}

  template <typename P> auto conf(Program const &p) {
    auto res = set_uniform(p, "xxxx", t);
    return res;
  }

private:
  ogl::texture t;
  GLuint uint;
};

template <template Program> auto conf(textured const &t, Program const &p) {
  return t.conf(p);
}

} // namespace oen
