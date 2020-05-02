#pragma once

namespace oen {
namespace materials {

// geomery, normal, tex
class phong : public materail {

  virtual auto active() const -> void {
    material::active();
    program_.set("u_color", color_);
  }
};

} // namespace materials
} // namespace oen
