#pragma once

#include <GLFW/glfw3.h>
#include "window_manager.h"
#include <memory>
#include <string>

namespace kito {
namespace glfw {

class GlfwWindowManager: public WindowManager {
 public:
  static std::unique_ptr<GlfwWindowManager> CreateWindow(int width, int height, std::string title);
  GlfwWindowManager(int width, int height, std::string title);
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
