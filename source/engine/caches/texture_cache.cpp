#include <iostream>
#include "texture_cache.hpp"

TextureCache::~TextureCache(){
  dispose();
}
void TextureCache::dispose(){
  texture_map_.clear();
}
sf::Texture& TextureCache::GetTexture(const std::string& file_name) {
  auto [it, inserted] = texture_map_.try_emplace(file_name);
  if (inserted && !it->second.loadFromFile(file_name)) {
    std::cerr << "Error: failed to load texture [" << file_name << "]." << std::endl;
  }
  return it->second;
}