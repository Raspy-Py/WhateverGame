#ifndef WHATEVERGAME_SOURCE_ENGINE_CACHES_FONT_CACHE_HPP_
#define WHATEVERGAME_SOURCE_ENGINE_CACHES_FONT_CACHE_HPP_
#include <string>
#include <unordered_map>
#include "SFML/Graphics/Font.hpp"
class FontCache {
 public:
  FontCache() = default;
  ~FontCache();
  void dispose();
  sf::Font& GetFont(const std::string& file_name);

 private:
  std::unordered_map<std::string, sf::Font> font_map_;
};

#endif //WHATEVERGAME_SOURCE_ENGINE_CACHES_FONT_CACHE_HPP_
