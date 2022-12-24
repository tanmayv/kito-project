#pragma once
#include <string>
#include <memory>
#include "shader.h"
#include "model.h"
#include "texture.h"

namespace kito {

class AssetReader {
 public:
  virtual std::string ReadAsset(std::string asset_path) = 0;
  virtual std::shared_ptr<Shader> LoadShader(std::string raw_vertex_shader,
                                     std::string raw_fragment_shader) = 0;
  virtual std::shared_ptr<Model> LoadModel(Mesh mesh) = 0;
  virtual std::shared_ptr<Texture> LoadTexture(std::string texture_path) = 0;
};

}  // namespace kito
