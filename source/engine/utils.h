#ifndef WHATEVERGAME_SOURCE_ENGINE_UTILS_H_
#define WHATEVERGAME_SOURCE_ENGINE_UTILS_H_

#include "yaml-cpp/yaml.h"
#include "SFML/Graphics.hpp"
#include "engine/GUI/blocks.h"


template<typename T>
T ParseAs(const YAML::Node& node);

template<>
sf::Vector2i ParseAs(const YAML::Node& node){
  return {node[0].as<int>(), node[1].as<int>()};
}

template<>
sf::Vector2f ParseAs(const YAML::Node& node){
  return {node[0].as<float>(), node[1].as<float>()};
}

template<>
sgui::Block::ContentAreaType ParseAs(const YAML::Node& node){
  auto str = node.as<std::string>();
  if (str == "relative") return sgui::Block::Relative;
  else if (str == "absolute") return sgui::Block::Absolute;
  else return sgui::Block::Invalid;
}

#endif //WHATEVERGAME_SOURCE_ENGINE_UTILS_H_
