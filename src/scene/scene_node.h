#pragma once
#include "scene/scene_node_properties.h"
#include "scene/scene.h"
#include "glm/glm.hpp"
#include "kito_common.h"
#include <memory>
#include <vector>
#include <string>
#include "scene/scene_node_interface.h"

namespace kito {
class Scene;

typedef std::vector<std::shared_ptr<SceneNodeInterface>> SceneNodeList;

class SceneNode : public SceneNodeInterface {
  friend class Scene;

 protected:
  SceneNodeList children_ = {};
  SceneNode* parent_ = nullptr;
  SceneNodeProperties props_ = {};

 public:
  SceneNode(ActorId actor_id, std::string name, RenderPass render_pass,
            const Color& diffuse_color, const Mat4x4* to, const Mat4x4* from);
  virtual const SceneNodeProperties* Props() const override;
  virtual void SetTransform(const glm::fmat4x4* to_world,
                            const glm::fmat4x4* from_world = NULL) override;
  virtual Result OnUpdate(Scene* scene, float elapsed_time) override;
  virtual Result OnRestore(Scene* scene) override;
  virtual Result PreRender(Scene* scene) override;
  virtual bool IsVisible(Scene* scene) const override;
  virtual Result Render(Scene* scene) override;
  virtual Result RenderChildren(Scene* scene) override;
  virtual Result PostRender(Scene* scene) override;
  virtual bool AddChild(std::shared_ptr<SceneNodeInterface> kid) override;
  virtual bool RemoveChild(ActorId id) override;
  void SetAlpha(float alpha);
  float GetAlpha();
  glm::fvec3 GetPosition();
  void SetPosition(const glm::fvec3& pos);

  // TODO: implement OnLostDevice
  virtual Result OnLostDevice(Scene* scene) override { return kOK; }

  virtual ~SceneNode() = default;

};
}  // namespace kito