#include <iostream>
#include "resource_manager.h"
#include "engine/caches/texture_cache.hpp"
#include "engine/caches/font_cache.hpp"

TextureCache ResourceManager::texture_cache_;
FontCache ResourceManager::font_cache_;

sf::Font ResourceManager::GetFont(const std::string& file_name){
  return font_cache_.GetFont(file_name);
}

sf::Texture ResourceManager::GetTexture(const std::string& file_name){
  return texture_cache_.GetTexture(file_name);
}
