#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace kito {

class WindowManager {
 public:
  static std::unique_ptr<WindowManager> Create();
  virtual void StartFrame() = 0;
  virtual void EndFrame() = 0;
  virtual void SetActive() = 0;
  virtual glm::vec2 GetDimensions() = 0;
  virtual bool ShouldClose() = 0;
};

}  // namespace kito
