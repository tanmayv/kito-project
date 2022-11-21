#include "scene/root_node.h"
#include "kito_common.h"
#include <memory>

namespace kito {

RootNode::RootNode()
    : SceneNode(-1, "Root", RenderPass_ZERO, glm::fvec4{}, &IDENTITY,
                nullptr) {
  children_.reserve(RenderPass_COUNT);
  std::shared_ptr<SceneNode> static_group(new SceneNode(
      -1, "Static Group", RenderPass_STATIC, WHITE, &IDENTITY, nullptr));
  children_.push_back(static_group);
  std::shared_ptr<SceneNode> actor_group(new SceneNode(
      -1, "Actor Group", RenderPass_ACTOR, WHITE, &IDENTITY, nullptr));
  children_.push_back(actor_group);
  std::shared_ptr<SceneNode> sky_group(new SceneNode(
      -1, "SKY Group", RenderPass_SKY, WHITE, &IDENTITY, nullptr));
  children_.push_back(sky_group);
  std::shared_ptr<SceneNode> invisible_group(new SceneNode(
      -1, "Invisible Group", RenderPass_NOT_RENDERED, WHITE, &IDENTITY, nullptr));
  children_.push_back(invisible_group);
}

bool RootNode::AddChild(std::shared_ptr<SceneNodeInterface> kid) {
  return children_[kid->Props()->GetRenderPass()]->AddChild(kid);
}

Result RootNode::RenderChildren(Scene* scene) {
  for (int pass = RenderPass_ZERO; pass < RenderPass_COUNT; ++pass) {
    switch (pass) {
      case RenderPass_STATIC:
      case RenderPass_ACTOR:
      case RenderPass_SKY:
        children_[pass]->RenderChildren(scene);
    }
  }
    
  return kOK;
}

bool RootNode::IsVisible(Scene* scene) const { return false; }
}  // namespace kito
