#ifndef WHATEVERGAME_SOURCE_ENGINE_RESOURCE_MANAGER_H_
#define WHATEVERGAME_SOURCE_ENGINE_RESOURCE_MANAGER_H_
#include "caches/texture_cache.hpp"
#include "caches/font_cache.hpp"


class ResourceManager {

 public:
  ResourceManager() = default;

  static sf::Font GetFont(const std::string& filename);
  static sf::Texture GetTexture(const std::string& filename);

 private:
  static FontCache font_cache_;
  static TextureCache texture_cache_;
};


#endif //WHATEVERGAME_SOURCE_ENGINE_RESOURCE_MANAGER_H_
