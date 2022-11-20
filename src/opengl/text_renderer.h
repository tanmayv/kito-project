#include <string>

namespace kito {
class TextRenderer {
 public:
  bool Init(std::string_view font_file, int font_size);
  void RenderText(int x, int y, std::string_view message, double scale);
};
}  // namespace kito