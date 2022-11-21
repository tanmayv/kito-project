#include "scene/scene.h"
#include "scene/scene_node.h"
#include "scene/camera_node.h"
#include "scene/root_node.h"

namespace kito {
Scene::Scene() {  // Create root_node
  root_ = std::make_shared<RootNode>();
}

Scene::~Scene() {}

Result Scene::OnRender() {
  if (root_ && camera_) {
    camera_->SetViewTransform(this);
    if (root_->PreRender(this) == kOK) {
      root_->Render(this); 
      root_->RenderChildren(this); 
      root_->PostRender(this); 
    }
  }
  RenderAlphaPass();
  return kOK;
}

Result Scene::OnRestore() {
  if (!root_) return kOK;
  return root_->OnRestore(this);
}

Result Scene::OnLostDevice() {
  if (!root_) return kOK;
  return root_->OnLostDevice(this);
}

Result Scene::OnUpdate(const float elapsed_time) {
  if (!root_) return kOK;
  return root_->OnUpdate(this, elapsed_time);
}

std::shared_ptr<SceneNodeInterface> Scene::FindActorById(ActorId id) {
  auto it = actor_map_.find(id);
  if (it == actor_map_.end()) return nullptr;
  return (*it).second;
}

bool Scene::AddChild(ActorId id, std::shared_ptr<SceneNodeInterface> kid) {
   
  // id < 0 belongs to root node child releated to render passe
  if (id > -1 && FindActorById(id) == nullptr) {
    actor_map_[id] = kid;
    return true;
  }
  return root_->AddChild(kid);
}

bool Scene::RemoveChild(ActorId id, std::shared_ptr<SceneNodeInterface> kid) {
  // id < 0 belongs to root node child releated to render passe
  if (id < 0) return false;

  auto kid_found = FindActorById(id);
  if (kid_found != nullptr) {
    actor_map_.erase(id);
    return true;
  }
  return root_->RemoveChild(id);
}

void Scene::PushAndSetMatrix(const glm::fmat4x4& to_world) {
  matrix_stack_.PushMatrix();
  matrix_stack_.LoadMatrix(to_world);
}

void Scene::PopMatrix() { matrix_stack_.PopMatrix(); }

const glm::mat4x4 Scene::GetTopMatrix() { return matrix_stack_.Peek(); }
}  // namespace kito