#ifndef WHATEVERGAME_SOURCE_ENGINE_UTILS_H_
#define WHATEVERGAME_SOURCE_ENGINE_UTILS_H_

#include "yaml-cpp/yaml.h"
#include "SFML/Graphics.hpp"
#include "engine/GUI/blocks.h"


template<typename T>
T ParseAs(const YAML::Node& node);


#endif //WHATEVERGAME_SOURCE_ENGINE_UTILS_H_
