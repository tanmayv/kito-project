#pragma once
#include "platform.h"
#include <string>
#include <functional>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace kito {
class GlfwPlatform: public Platform {
 public:
  GlfwPlatform(int width, int height, std::string_view window_name);
  ~GlfwPlatform();
  bool Init() override;
  void OnResize(std::function<void(int, int)> resize_callback) override;
  bool CloseRequested() override;
  void Update() override;
  void SwitchBuffer() override;
 private:
  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                    int mods);
  static void SizeCallback(GLFWwindow* window, int width,
                                        int height);
  static int width_;
  static int height_;
  static bool resized_;

  std::string window_name_;
  GLFWwindow* window_ = nullptr;
  std::function<void(int, int)> resize_callback_;
};
}