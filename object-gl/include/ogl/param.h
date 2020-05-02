#pragma once

#include <utility>
#include <memory>
#include <type_traits>

#include "program.h"

namespace ogl {

class shadable {
public:
  shadable() {}
  virtual ~shadable(){};
  virtual auto config(program &p) const -> bool = 0;
};

auto config(program &prog, shadable const &param) { return param.config(prog); }

template <typename Value> class param : public shadable {
public:
  param(std::string name, Value const &value) : name_(name), value_(value) {}
  virtual ~param() {}

  auto config(program &p) const -> bool override {
    return p.set(name_.c_str(), value_);
  }

private:
  std::string name_;
  std::decay_t<Value> value_;
};
//// deduction guide
// template <class Value>
// param(std::string name, Value &&value)->param<std::decay_t<Value>>;

template <typename Value>
auto make_param(std::string name, Value &&value) -> std::shared_ptr<shadable> {
  return std::make_shared<param>(name, std::forward<Value>(value));
}

/* Example
auto p_view = make_param("view", glm::mat4(xx));
... // make other parmas.
render(vertices, program, p_view, p_projection);

*/
} // namespace ogl
