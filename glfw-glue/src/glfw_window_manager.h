#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include "window_manager.h"

namespace kito {
namespace glfw {

class GlfwWindowManager: public WindowManager {
 public:
  static std::unique_ptr<GlfwWindowManager> CreateWindow();
  GlfwWindowManager();
  ~GlfwWindowManager();
  void StartFrame() override;
  void SetActive() override;
  void EndFrame() override;
  glm::vec2 GetDimensions() override;
  bool ShouldClose() override;
 private:
  GLFWwindow* window_;
};

}
}
