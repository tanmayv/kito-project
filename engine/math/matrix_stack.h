#pragma once
#include <glm/glm.hpp>
#include <stack>

namespace kito {
class MatrixStack {
 public:
  void LoadIdentity();
  void LoadMatrix(const glm::mat4x4 &mat);
  void MultMatrix(const glm::mat4x4 &mat);
  const glm::mat4x4 Peek();
  void PopMatrix();
  void PushMatrix();
  void Rotate(float radians, glm::fvec3 rotation_axis);
  void Scale(glm::fvec3 scale);
  void Translate(glm::fvec3 scale);

 private:
  std::stack<glm::fmat4x4> stack_ = {};
};
}