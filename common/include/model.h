
#pragma once

#include <vector>
#include <memory>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

namespace kito {

struct Vertex {
  glm::vec3 point;
  glm::vec2 uv;
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<int> indices;
};

enum class ModelType {
  kTextured_model
};

class Model {
 public:
  static std::shared_ptr<Model> CreateModel(Mesh mesh);
};

}  // namespace kito
