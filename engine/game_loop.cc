#include "game_loop.h"
#include <chrono>

namespace kito {

GameLoop::GameLoop(int target_fps, UpdateCallable callback)
    : target_fps_(target_fps), update_callback_(callback) {}

void GameLoop::Start() {
  auto current_time = std::chrono::system_clock::now();
  bool enabled = update_callback_ != nullptr;
  while (enabled) {
    auto new_time = std::chrono::system_clock::now();
    auto duration =
        new_time.time_since_epoch() - current_time.time_since_epoch();
    enabled = update_callback_(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()/1000.0f);
    current_time = new_time;
  }
}

}