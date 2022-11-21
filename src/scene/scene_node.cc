#include "scene/scene_node.h"
#include "kito_common.h"

namespace kito {

SceneNode::SceneNode(ActorId actor_id, std::string name, RenderPass render_pass,
          const Color& diffuse_color, const Mat4x4* to, const Mat4x4* from)
    : parent_(nullptr) {
  props_.actor_id_ = actor_id;
  props_.name_ = name;
  props_.render_pass_ = render_pass;
  props_.material_.SetDiffuseColor(diffuse_color);
  props_.material_.alpha_ = 1.0f;
  SetTransform(to, from);
}

const SceneNodeProperties* SceneNode::Props() const { return &props_; };

void SceneNode::SetTransform(const glm::fmat4x4* to_world,
                             const glm::fmat4x4* from_world) {
  props_.to_world_ = *to_world;
  // TODO() Calculate inverse matrix here 
}

void SceneNode::SetAlpha(float alpha) { 
    props_.material_.alpha_ = alpha; 
}

float SceneNode::GetAlpha() { return props_.material_.alpha_; }

glm::fvec3 SceneNode::GetPosition() {
  return glm::fvec3(props_.to_world_[3].x, props_.to_world_[3].y, props_.to_world_[3].z);
}

void SceneNode::SetPosition(const glm::fvec3& pos) {
  props_.to_world_[3].x = pos.x;
  props_.to_world_[3].y = pos.y;
  props_.to_world_[3].z = pos.z;
}

Result SceneNode::OnUpdate(Scene* scene, float elapsed_time) {
  for (const auto& node : children_) {
    node->OnUpdate(scene, elapsed_time);
  }
  return kOK;
}

Result SceneNode::OnRestore(Scene* scene)  {
  for (const auto& node : children_) {
    node->OnRestore(scene);
  }
  return kOK;
}

Result SceneNode::PreRender(Scene* scene) {
  scene->PushAndSetMatrix(props_.to_world_);
  return kOK;
}

bool SceneNode::IsVisible(Scene* scene) const {
  // Get Camera's frustum from the scene and check visibility later
  return true;
}

Result SceneNode::Render(Scene* scene) {
  return kOK;
}

Result SceneNode::RenderChildren(Scene* scene)  {
  for (const auto& node : children_) {
    if (node->PreRender(scene) == kOK) {
      if (node->IsVisible(scene)) {
        auto alphaType = node->Props()->material_.GetAlphaType();
        if (alphaType == AlphaType::kOpaque) {
          node->Render(scene); 
        } else if (alphaType != AlphaType::kTransparent) {
            // Add To scene's alpha list
            // Render it later in Scene's alpha pass from the scene
        }
      }
      node->RenderChildren(scene);
    }
    node->PostRender(scene);
  }
  return kOK;
}

Result SceneNode::PostRender(Scene* scene)  {
  scene->PopMatrix();
  return kOK;
}

bool SceneNode::AddChild(std::shared_ptr<SceneNodeInterface> kid)  {
  children_.push_back(kid);
  // update bounding box wrt to child's bounding box
  return true;
}
bool SceneNode::RemoveChild(ActorId id) {
  int index = 0;
  for (const auto& node : children_) {
    if (node->Props()->actor_id_ == id) {
      children_.erase(children_.begin() + index);
      // Update any bounding boxes
      return true;
    }
    index++;
  }
  return false;
}

}  // namespace
