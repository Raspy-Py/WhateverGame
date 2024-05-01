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

  template <typename T>
  T& Get(const std::string& file_name);

  // Template specializations for each supported type
  template<>
  sf::Texture& Get<sf::Texture>(const std::string& name);
  template<>
  sf::Font& Get<sf::Font>(const std::string& name);

 private:
  std::unordered_map<std::string, std::string> file_map_; // resource_name -> file_name
  std::unordered_map<std::string, std::unique_ptr<sf::Font>> font_map_; // resource_name -> resource
  std::unordered_map<std::string, std::unique_ptr<sf::Texture>> texture_map_; // resource_name -> resource
  
 private:
  ResourceManager() = default;
};


#endif //WHATEVERGAME_SOURCE_ENGINE_RESOURCE_MANAGER_H_
