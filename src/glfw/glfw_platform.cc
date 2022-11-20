#include "glfw/glfw_platform.h"
#include <fmt/core.h>

namespace kito {
namespace {
void error_callback(int error, const char* description) {
  fmt::print("glfw_error: error_code {}; {}", error, description);
}
}  // namespace
int GlfwPlatform::width_ = 0;
int GlfwPlatform::height_ = 0;
bool GlfwPlatform::resized_ = false;

GlfwPlatform::GlfwPlatform(int w, int h, std::string_view window_name)
    : window_name_(window_name) {
  GlfwPlatform::width_ = w;
  GlfwPlatform::height_ = h;
}

GlfwPlatform::~GlfwPlatform() {
  if (window_ != nullptr) {
    glfwDestroyWindow(window_);
  }
  glfwTerminate();
}

void GlfwPlatform::KeyCallback(GLFWwindow* window, int key, int scancode,
                               int action, int mods) {
  fmt::print("Key Event: {}, {}, {}, {} \n", key, scancode, action, mods);
}

void GlfwPlatform::SizeCallback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  // glViewport(0, 0, width, height;
   
  GlfwPlatform::width_ = width;
  GlfwPlatform::height_ = height;
  resized_ = true;
}

bool GlfwPlatform::Init() {

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) return false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width_, height_, window_name_.c_str(), NULL, NULL);
  if (!window_) {
    return false;
  }

  glfwSetKeyCallback(window_, KeyCallback);
  glfwSetFramebufferSizeCallback(window_, SizeCallback);
  glfwMakeContextCurrent(window_);
  return true;
}

void GlfwPlatform::OnResize(std::function<void(int, int)> resize_callback) {
  resize_callback_ = resize_callback;
}

bool GlfwPlatform::CloseRequested() { return glfwWindowShouldClose(window_); }

void GlfwPlatform::Update() {
  glfwSwapBuffers(window_);
  glfwPollEvents();
  if (resized_ && resize_callback_) {
    resize_callback_(GlfwPlatform::width_, GlfwPlatform::height_);
    resized_ = false;
  }
}

}  // namespace kito