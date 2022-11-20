#pragma once
#include "scene/scene_node_properties.h"
#include "scene/scene.h"
#include "glm/glm.hpp"
#include "kito_common.h"
#include <memory>

namespace kito {
class SceneNodeInterface {
 public:
  virtual const SceneNodeProperties* Props() const = 0;
  virtual void VSetTransform(const glm::fmat4x4 *to_world,
                             const glm::fmat4x4 *from_world = NULL) = 0;
  virtual Result OnUpdate(Scene* scene, float elapsed_time) = 0;
  virtual Result OnRestore(Scene* scene) = 0;
  virtual Result PreRender(Scene* scene) = 0;
  virtual bool IsVisible(Scene* scene) = 0;
  virtual Result Render(Scene* scene) = 0;
  virtual Result RenderChildren(Scene* scene) = 0;
  virtual Result PostRender(Scene* scene) = 0;
  virtual Result PostRender(Scene* scene) = 0;
  virtual bool AddChild(std::shared_ptr<SceneNodeInterface> kid) = 0;
  virtual bool RemoveChild(ActorId id) = 0;
  virtual Result OnLostDevice(Scene* scene) = 0;

  virtual ~SceneNodeInterface(Scene* scene){};
};
}  // namespace kito