#pragma once
namespace kito {

class Global {
  int width_;
  int height_;
  float scale_;

 public:
  int Width() const { return width_ * scale_; }
  int Height() const { return height_ * scale_; }
  void SetWidth(int w) { width_ = w; }
  void SetHeight(int h) { height_ = h; }
  void SetScale(float s) { scale_ = s; }
};

static Global global{};
}  // namespace kito