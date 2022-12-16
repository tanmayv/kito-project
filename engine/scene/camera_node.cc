#include "scene/camera_node.h"
#include "global.h"
#include "glm/ext.hpp"

namespace kito {

  CameraNode::CameraNode(const glm::mat4x4* transform)
    : SceneNode(-1, "Camera", RenderPass_ZERO, WHITE, transform, nullptr) {
  
        projection_ = glm::ortho(0.0f, (float)global.Width(),
                             (float)global.Height(), 0.0f, -1000.f, 1000.f);
  }

Result CameraNode::OnRestore(Scene* scene) {
  // Update matrices on display size changes
  return kOK;
}
Result CameraNode::SetViewTransform(Scene* scene) { 
    // Set Camera position and orientation to the rendering device
    return kOK; 
}
glm::mat4x4 CameraNode::GetWorldViewProjection(Scene* scene) { return {}; }
}  // namespace kito