#include "ogl/loader.h"
#include <fmt/format.h>
#include <filesystem>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace ogl {
auto load_texture(std::string const &file)
    -> std::tuple<GLsizei, GLsizei, GLenum, GLenum, std::shared_ptr<void>> {
  GLsizei width = 0, height = 0, channels = 0;

  // unsigned char *image =
  // SOIL_load_image(file.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
  unsigned char *image = stbi_load(file.c_str(), &width, &height, &channels, 0);

  if (!image) {
    fmt::print("failed to load image {}", file.c_str());
    return {};
  }

  // auto data = std::shared_ptr<void>(
  // image, [](unsigned char *i) { SOIL_free_image_data(i); });
  auto data = std::shared_ptr<void>(
      image, [](unsigned char *i) { stbi_image_free(i); });

  // setup forrmat
  auto format = (channels == 4) ? GL_RGBA : GL_RGB;

  return {width, height, format, GL_UNSIGNED_BYTE, data};
}

auto load_shader(std::string const &filepath) -> std::string {
  namespace fs = std::filesystem;
  fs::path p{filepath};

  std::ifstream ifs(p.string());
  if (!ifs.is_open()) {
    fmt::print("failed to load shader {}", filepath);
    return "";
  }

  // Read all the text into a string
  std::stringstream ss;
  ss << ifs.rdbuf();
  return ss.str();
}
}  // namespace ogl

