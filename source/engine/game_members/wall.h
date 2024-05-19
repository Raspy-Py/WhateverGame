#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_WALL_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_WALL_H_

#include "gameobject.h"

class Wall : public GameObject {
 public:
  Wall(sf::Texture &texture, sf::Vector2f size);
  ~Wall() override = default;

};

#endif // WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_WALL_H_
