#include "scene/scene_node.h"
#include <memory>

namespace kito {
class RootNode : public SceneNode {
 public:
  RootNode();
  virtual bool AddChild(std::shared_ptr<SceneNodeInterface> kid) override;
  virtual Result RenderChildren(Scene* scene) override;
  virtual bool IsVisible(Scene* scene) const override;
};
}