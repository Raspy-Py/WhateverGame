#include <iostream>
#include "font_cache.hpp"

FontCache::~FontCache(){
  dispose();
}

void FontCache::dispose(){
  if (font_map_.empty()) return;
  for (auto& font : font_map_) {
    font.second.~Font();
  }
}

sf::Font FontCache::GetFont(const std::string& file_name){
  if (font_map_.find(file_name) == font_map_.end()){
    std::cout << "font not found in cache, loading from file\n";
    sf::Font font;
    if (!font.loadFromFile(file_name))
      std::cerr << "Error: failed to load font [" << file_name << "]. " << std::endl;
    font_map_[file_name] = font;
  } else {
    std::cout << "font found in cache\n";
  }

  return font_map_[file_name];

}