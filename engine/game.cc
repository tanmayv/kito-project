#include "game.h"
#include "game_loop.h"
#include "window_manager.h"

namespace kito {
Game::Game(GameOptions game_options):
  window_manager_(WindowManager::Create(game_options.width,
                                        game_options.height,
                                        game_options.title)) {
  window_manager_->SetActive();
}

void Game::StartGameLoop() {
  GameLoop loop(60, [&](const double delta_time){
                  window_manager_->StartFrame();

                  window_manager_->EndFrame();
                  return !window_manager_->ShouldClose();
                });
  loop.Start();
}
}
