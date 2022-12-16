#pragma once
#include "kito_common.h"
#include "math/matrix_stack.h"
#include "render/renderer_interface.h"
#include <map>
#include <memory>

namespace kito {
class CameraNode;
class SceneNode;
class SceneNodeInterface;
typedef std::map<ActorId, std::shared_ptr<SceneNodeInterface>> SceneActorMap;
class Scene {
 protected:
  std::shared_ptr<SceneNode> root_;
  std::shared_ptr<CameraNode> camera_;
  std::shared_ptr<RendererInterface> renderer_;
  MatrixStack matrix_stack_ = {};
  SceneActorMap actor_map_;
  void RenderAlphaPass(){};

 public:
  Scene();
  ~Scene();
  RendererInterface* Renderer() { return renderer_.get(); }
  Result OnRender();
  Result OnRestore();
  Result OnLostDevice();
  Result OnUpdate(const float elapsed_time);
  std::shared_ptr<SceneNodeInterface> FindActorById(ActorId id);
  bool AddChild(ActorId id, std::shared_ptr<SceneNodeInterface> kid);
  bool RemoveChild(ActorId id, std::shared_ptr<SceneNodeInterface> kid);
  void SetCamera(std::shared_ptr<CameraNode> camera) { camera_ = camera; }
  const std::shared_ptr<CameraNode> GetCamera() { return camera_; }
  void PushAndSetMatrix(const glm::fmat4x4 &to_world);
  void PopMatrix();
  const glm::mat4x4 GetTopMatrix();
};
}  // namespace kito