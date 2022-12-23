#pragma once
#include <memory>
#include <string>

#include "window_manager.h"
#include "scene/scene.h"

namespace kito {

struct GameOptions {
  int width, height;
  std::string title;
};

class Game {
 public:
  explicit Game(GameOptions options);
  void SetCurrentScene(std::shared_ptr<Scene> scene);
  void StartGameLoop();

 private:
  std::unique_ptr<WindowManager> window_manager_;
  std::shared_ptr<Scene> current_scene_;
};
}  // namespace kito
