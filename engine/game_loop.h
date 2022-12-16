#include<functional>

namespace kito {
using UpdateCallable = std::function<bool(double)>;
class GameLoop {
 public:
  GameLoop(int target_fps, UpdateCallable callable);
  void Start();

 private:
  int target_fps_ = 60;
  UpdateCallable update_callback_ = nullptr;
};
}