#include <iostream>
#include "font_cache.hpp"

FontCache::~FontCache(){
  dispose();
}

void FontCache::dispose(){
  font_map_.clear();
}

sf::Font& FontCache::GetFont(const std::string& file_name) {
  auto [it, inserted] = font_map_.try_emplace(file_name);
  if (inserted && !it->second.loadFromFile(file_name)) {
    std::cerr << "Error: failed to load font [" << file_name << "]." << std::endl;
  }
  return it->second;
}