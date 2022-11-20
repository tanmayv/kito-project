#pragma once
#include <functional>

namespace kito {
class Platform {
 public:
  virtual bool Init() = 0;
  virtual void OnResize(std::function<void(int, int)> resize_callback) = 0;
  virtual bool CloseRequested() = 0;
  virtual void Update() = 0;
};
}  // namespace kito