#pragma once
#include "kito_common.h"
namespace kito {
enum class AlphaType { kOpaque, kTranslucent, kTransparent };
struct Material {
  Color diffuse_color_;
  float alpha_;

  AlphaType GetAlphaType() const {
    if (alpha_ < 0.001f) {
      return AlphaType::kTransparent;
    }
    if (alpha_ > 0.999f) {
      return AlphaType::kOpaque;
    }
    return AlphaType::kTranslucent;
  }

  void SetDiffuseColor(const Color& color) {
    diffuse_color_ = glm::fvec4(color);
  }
};
}  // namespace kito
