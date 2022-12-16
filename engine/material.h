#pragma once
#include "opengl/shader.h"
#include "opengl/texture.h"
#include <glm/glm.hpp>
namespace kito {
struct Material {
  std::string shader_name; 
  std::string texture_name;
  glm::ivec3 color;
};
}  // namespace kito