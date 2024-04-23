#ifndef WHATEVERGAME_SOURCE_ENGINE_CACHES_TEXTURE_CACHE_HPP_
#define WHATEVERGAME_SOURCE_ENGINE_CACHES_TEXTURE_CACHE_HPP_
#include <string>
#include <unordered_map>
#include "SFML/Graphics/Texture.hpp"

class TextureCache {
 public:
  TextureCache() = default;
  ~TextureCache();
  void dispose();
  sf::Texture& GetTexture(const std::string& file_name);

 private:
  std::unordered_map<std::string, sf::Texture> texture_map_;
};


#endif //WHATEVERGAME_SOURCE_ENGINE_CACHES_TEXTURE_CACHE_HPP_
