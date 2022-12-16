#pragma once
#include "kito_common.h"
namespace kito {
class RendererInterface {
 public:
  virtual void OnRestore() = 0;
  virtual void ClearBackground() = 0;
};
}  // namespace kito