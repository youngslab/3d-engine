#pragma once

#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ogl {

class program : public resource {
 public:
  program(shader const &vertex, shader const &fragment);

  auto bind() const -> void;
  auto unbind() const -> void;

  template <typename T>
  auto set(const char *name, T const &value) const;

 private:
  GLuint id_;
};

template <>
inline auto program::set<int>(const char *name, int const &value) const {
  glUniform1i(glGetUniformLocation(id_, name), value);  // set it manually
}

template <>
inline auto program::set<glm::mat4>(const char *name,
				    glm::mat4 const &value) const {
  glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
		     glm::value_ptr(value));  // set it manually
}

template <>
inline auto program::set<glm::vec4>(const char *name,
				    glm::vec4 const &value) const {
  glUniform4fv(glGetUniformLocation(id_, name), 1,
	       glm::value_ptr(value));  // set it manually
}

}  // namespace ogl
