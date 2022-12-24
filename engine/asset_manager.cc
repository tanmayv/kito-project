#include "asset_manager.h"
#include "texture.h"
#include <functional>
#include <memory>

namespace kito {
namespace {
  template<typename T>
  void AddIfNotPresent(std::map<std::string, T> *map, std::string key,
                       std::function<T()> creator) {
    if (map->find(key) != map->end()) map->insert({key, creator()});
  }

  template<typename T>
  std::shared_ptr<T> ReadMap(std::map<std::string, std::shared_ptr<T>>
                             *map, std::string key) {
    auto it = map->find(key);
    if (it != map->end()) return it->second;
    return nullptr;
  }
}  // namespace

AssetManager::AssetManager(AssetReader* asset_reader):
  asset_reader_(asset_reader) {}
void AssetManager::CreateShaderFromRawString(std::string name,
                                             std::string raw_vertex_shader,
                                             std::string raw_fragment_shader) {
  AddIfNotPresent<std::shared_ptr<Shader>>(&shader_map, name, [&]() {
                    return asset_reader_->LoadShader(raw_vertex_shader,
                                                     raw_fragment_shader);});
}
void AssetManager::CreateShaderFromAsset(std::string name, std::string vertex_path,
                                         std::string fragment_path) {
  AddIfNotPresent<std::shared_ptr<Shader>>(&shader_map, name, [&]() {
        return asset_reader_->LoadShader(asset_reader_->ReadAsset(vertex_path),
                                         asset_reader_->
                                         ReadAsset(fragment_path));});
}
std::shared_ptr<Shader> AssetManager::LoadShader(std::string shader_name) {
  return ReadMap<Shader>(&shader_map, shader_name);
}

void AssetManager::CreateModelFromMesh(std::string name, Mesh mesh) {
  AddIfNotPresent<std::shared_ptr<Model>>(&model_map, name, [&] () {
                                      return asset_reader_->LoadModel(mesh);});
}

std::shared_ptr<Model> AssetManager::LoadModel(std::string model_name) {
  return ReadMap<Model>(&model_map, model_name);
}

void AssetManager::CreateTextureFromAsset(std::string name,
                                          std::string texture_path) {
  AddIfNotPresent<std::shared_ptr<Texture>>(&texture_map, name, [&] () {
                            return asset_reader_->LoadTexture(texture_path);});
}

std::shared_ptr<Texture> AssetManager::LoadTexture(std::string name) {
  return ReadMap<Texture>(&texture_map, name);
}

}
