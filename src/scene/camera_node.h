#pragma once
#include "scene/scene_node.h"
#include "scene/scene.h"
#include <glm/glm.hpp>

namespace kito {
class CameraNode : public SceneNode {
 public:
  CameraNode(const glm::mat4x4 *transform);
  virtual Result OnRestore(Scene* scene) override;
  // Send camera position and orientation to the rendering device
  virtual Result SetViewTransform(Scene* scene);
  // Used convert object space to ScreenSpace
  glm::mat4x4 GetWorldViewProjection(Scene* scene);

  glm::mat4x4 GetProjection(Scene* scene) { return projection_; }
  glm::mat4x4 GetView(Scene* scene) { return view_; }

  void SetCameraOffset(const glm::vec4& camera_offset) {
    camera_offset_ = camera_offset;
  }

 protected:
  glm::mat4x4 projection_;
  glm::mat4x4 view_;
  bool active_;
  glm::vec4 camera_offset_;
};
}  // namespace kito