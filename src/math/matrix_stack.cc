#include "math/matrix_stack.h"
#include <glm/ext.hpp>
namespace kito {

void MatrixStack::LoadIdentity() {
  PopMatrix();
  stack_.push(glm::mat4x4{});
}

void MatrixStack::LoadMatrix(const glm::mat4x4 &mat) {
  PopMatrix();
  stack_.push(glm::mat4x4{mat});
}

void MatrixStack::MultMatrix(const glm::mat4x4 &mat) {
  glm::mat4x4 top = stack_.top();
  PopMatrix();
  stack_.push(glm::matrixCompMult(top, mat));
}

const glm::mat4x4 MatrixStack::Peek() { return stack_.top(); }

void MatrixStack::PopMatrix() {
  if (stack_.empty()) return;
  PopMatrix();
}

void MatrixStack::PushMatrix() {
  auto duplicate = glm::mat4x4(stack_.top());
  stack_.push(duplicate);
}

void MatrixStack::Rotate(float radians, glm::fvec3 rotation_axis) {
  glm::mat4x4 top = stack_.top();
  PopMatrix();
  stack_.push(glm::rotate(top, radians, rotation_axis));
}
void MatrixStack::Scale(glm::fvec3 scale) {
  glm::mat4x4 top = stack_.top();
  PopMatrix();
  stack_.push(glm::scale(top, scale));
}

void MatrixStack::Translate(glm::fvec3 translate) {
  glm::mat4x4 top = stack_.top();
  PopMatrix();
  stack_.push(glm::translate(top, translate));
}

}  // namespace kito
