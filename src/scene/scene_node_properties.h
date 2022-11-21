#pragma once
#include <string>
#include <glm/glm.hpp>
#include "render.h"
#include "kito_common.h"

namespace kito {

struct SceneNodeProperties {
  friend class SceneNode;
 protected:
  ActorId actor_id_;
  std::string name_;
  Mat4x4 to_world_;
  Mat4x4 from_world_;
  Vec4 bounding_box;  // x1, x2, y1, y2
  RenderPass render_pass_;
  Material material_;

 public:
  RenderPass GetRenderPass() const { return render_pass_; }
};
}  // namespace kito