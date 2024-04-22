#include <iostream>
#include "texture_cache.hpp"

TextureCache::~TextureCache(){
  dispose();
}
void TextureCache::dispose(){
  if (texture_map_.empty()) return;
  for (auto& texture : texture_map_){
    texture.second.~Texture();
  }
}
sf::Texture TextureCache::GetTexture(const std::string& file_name){
  if (texture_map_.find(file_name) == texture_map_.end()){
    sf::Texture texture;
    if (!texture.loadFromFile(file_name))
      std::cerr << "Error: failed to load texture [" << file_name << "]. " << std::endl;
    texture_map_[file_name] = texture;
  }
  return texture_map_[file_name];
}