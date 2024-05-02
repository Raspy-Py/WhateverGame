#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Player {
 public:
  Player(sf::Texture &texture, sf::Vector2f size);
  ~Player() = default;
  void Move(float distance);
  void Rotate(float radians);
  void Animate();
  void Draw(sf::RenderWindow &window) const;

  sf::Vector2f GetPosition() const {return position_; }
  float GetDirection() const { return direction_; }
  void SetDirection(float direction) { direction_ = direction; Animate(); }
  void SetPosition(const sf::Vector2f& position) {position_ = position; Animate(); }

 private:
  sf::Sprite sprite_;
  sf::Texture &texture_;

  float speed_ = 100.f;
  float rotation_speed_ = 1.f;
  float direction_;
  sf::Vector2f position_;
  sf::Vector2f player_size_;
};







#endif //WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
