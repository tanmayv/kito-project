#include <memory>

#include "glfw_window_manager.h"

namespace kito {

std::unique_ptr<WindowManager> WindowManager::Create(int width, int height,
                                                     std::string title) {
  return glfw::GlfwWindowManager::CreateWindow(width, height, title);
}

namespace glfw {

std::unique_ptr<GlfwWindowManager> GlfwWindowManager::CreateWindow(int width,
                                                                   int height,
                                                                   std::string title) {
  auto ptr = std::make_unique<GlfwWindowManager>(width, height, title);
  if (ptr->window_ == NULL) {
    return nullptr;
  }
  return ptr;
}

GlfwWindowManager::GlfwWindowManager(int width, int height, std::string title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
}

GlfwWindowManager::~GlfwWindowManager() {
  glfwTerminate();
}

void GlfwWindowManager::SetActive() {
  glfwMakeContextCurrent(window_);
  // TODO(tanmay): set frame buffer size callback
}

void GlfwWindowManager::StartFrame() {}

void GlfwWindowManager::EndFrame() {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

glm::vec2 GlfwWindowManager::GetDimensions() {
  glm::ivec2 dim;
  glfwGetWindowSize(window_, &dim.x, &dim.y);
  return dim;
}

bool GlfwWindowManager::ShouldClose() {
  return glfwWindowShouldClose(window_);
}

}  // namespace glfw
}  // namespace kito

