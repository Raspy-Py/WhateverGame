#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_

#include "gameobject.h"
#include <iostream>

class Player : public GameObject {
 public:
  Player(sf::Texture &texture, sf::Vector2f size);
  ~Player() override = default;

  void Move(float distance);
  void Rotate(float radians);


 private:
  float speed_ = 100.f;
  float rotation_speed_ = 1.f;
};

#endif // WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
