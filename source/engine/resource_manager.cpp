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
}

ResourceManager& ResourceManager::GetInstance() {
  static std::mutex mutex;
  std::lock_guard<std::mutex> lock(mutex);
  static ResourceManager instance;
  return instance;
}

template<>
sf::Texture& ResourceManager::Get<sf::Texture>(const std::string& name) {
  auto [it, inserted] = texture_map_.try_emplace(name);
  if (inserted && !it->second->loadFromFile(name)) {
    if (auto pfile = file_map_.find(name); pfile == file_map_.end() || !it->second->loadFromFile(pfile->second)) {
      std::cerr << "Error: failed to load texture [" << name << "]." << std::endl;
    }
  } else{
    std::cerr << "Error: texture [" << name << "] does not exist." << std::endl;
  }
  return *(it->second);
}

template<>
sf::Font& ResourceManager::Get<sf::Font>(const std::string& name) {
  auto [it, inserted] = font_map_.try_emplace(name);
  if (inserted && !it->second->loadFromFile(name)) {
    if (auto pfile = file_map_.find(name); pfile == file_map_.end() || !it->second->loadFromFile(pfile->second)) {
      std::cerr << "Error: failed to load font [" << name << "]." << std::endl;
    }
  } else{
    std::cerr << "Error: font [" << name << "] does not exist." << std::endl;
  }
  return *(it->second);
}
