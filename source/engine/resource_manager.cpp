#include "resource_manager.h"

#include "yaml-cpp/yaml.h"
#include "utils.h"

void ResourceManager::LoadResourceMap(const std::string &resources) {
  YAML::Node mapping = YAML::LoadFile(resources);

  for (auto resource_group : mapping){
    for (auto resource : resource_group.second) {
      auto name = resource.first.as<std::string>();
      auto file = resource.second.as<std::string>();
      file_map_[name] = file;
    }
  }

  font_map_.clear();
  texture_map_.clear();

  font_map_.reserve(100);
  texture_map_.reserve(100);
}

ResourceManager& ResourceManager::GetInstance() {
  static std::mutex mutex;
  std::lock_guard<std::mutex> lock(mutex);
  static ResourceManager instance;
  return instance;
}
