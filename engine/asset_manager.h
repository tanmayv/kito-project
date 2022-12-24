#pragma once
#include <string>
#include <map>
#include <memory>
#include "shader.h"
#include "model.h"
#include "texture.h"
#include "asset_reader.h"

namespace kito {
class AssetManager {
 public:
  explicit AssetManager(AssetReader* asset_reader);
  void CreateShaderFromRawString(std::string name,
                                 std::string raw_vertex_shader,
                                 std::string raw_fragment_shader);
  void CreateShaderFromAsset(std::string name, std::string vertex_path,
                             std::string fragment_path);
  std::shared_ptr<Shader> LoadShader(std::string shader_name);

  void CreateModelFromMesh(std::string name, Mesh mesh);

  std::shared_ptr<Model> LoadModel(std::string model_name);

  void CreateTextureFromAsset(std::string name, std::string texture_path);

  std::shared_ptr<Texture> LoadTexture(std::string name);

 private:
  std::map<std::string, std::shared_ptr<Shader>> shader_map;
  std::map<std::string, std::shared_ptr<Model>> model_map;
  std::map<std::string, std::shared_ptr<Texture>> texture_map;
  AssetReader* asset_reader_;
};
}
