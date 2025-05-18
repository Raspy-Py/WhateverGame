#ifndef WHATEVERGAME_SOURCE_ENGINE_RESOURCE_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_RESOURCE_MANAGER_H_

#include <memory>
#include <iostream>
#include <unordered_map>

#include "SFML/Graphics.hpp"

class ResourceManager {
 public:
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  static ResourceManager& GetInstance();
  void LoadResourceMap(const std::string& resources);

  // Template specializations for each supported type
  sf::Texture& GetTexture(const std::string& name) {
    auto [it, inserted] = texture_map_.try_emplace(name);
    if (inserted) {
      if (auto pfile = file_map_.find(name); pfile == file_map_.end() || !it->second.loadFromFile(pfile->second)) {
        std::cerr << "Error: failed to load texture [" << name << "]." << std::endl;
      }
    } else{
      std::cerr << "Error: texture [" << name << "] does not exist." << std::endl;
    }
    return it->second;
  }

  sf::Font& GetFont(const std::string& name) {
    auto [it, inserted] = font_map_.try_emplace(name);
    if (inserted) {
      if (auto pfile = file_map_.find(name); pfile == file_map_.end() || !it->second.loadFromFile(pfile->second)) {
        std::cerr << "Error: failed to load font [" << name << "]." << std::endl;
      }
    } else{
      std::cerr << "Error: font [" << name << "] does not exist." << std::endl;
    }
    return it->second;
  }

 private:
  std::unordered_map<std::string, std::string> file_map_; // resource_name -> file_name
  std::unordered_map<std::string, sf::Font> font_map_; // resource_name -> resource
  std::unordered_map<std::string, sf::Texture> texture_map_; // resource_name -> resource

 protected:
  ResourceManager() = default;
};


#endif //WHATEVERGAME_SOURCE_ENGINE_RESOURCE_MANAGER_H_
