#pragma once

#include "shader.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ogl {

class program : public resource {
public:
  program(shader const &vertex, shader const &fragment);

  auto bind() -> void;
  auto unbind() -> void;

  template <typename T> auto set(const char *name, T const &value) -> bool;

private:
  GLuint id_;
  /**
   * @brief It holds current texture unit number. It will be init when unbind.
   * Client have resoposibility to unbind when it finish to use the program.
   */
  GLuint texture2d_unit_;
};

template <>
inline auto program::set<int>(const char *name, int const &value) -> bool {
  glUniform1i(glGetUniformLocation(id_, name), value); // set it manually
  return true;
}

template <>
inline auto program::set<glm::mat4>(const char *name, glm::mat4 const &value)
    -> bool {
  glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
		     glm::value_ptr(value)); // set it manually
  return true;
}

template <>
inline auto program::set<glm::vec4>(const char *name, glm::vec4 const &value)
    -> bool {
  glUniform4fv(glGetUniformLocation(id_, name), 1,
	       glm::value_ptr(value)); // set it manually
  return true;
}

template <>
inline auto program::set<texture>(const char *name, ogl::texture const &t)
    -> bool {
  glUniform1i(glGetUniformLocation(id_, name), texture2d_unit_);
  glActiveTexture(GL_TEXTURE0 + texture2d_unit_);
  t.bind();
  texture2d_unit_++;
  return true;
}

static auto bind(program &p) { p.bind(); }
static auto unbind(program &p) { p.unbind(); }

} // namespace ogl
