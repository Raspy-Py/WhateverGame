#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Player {

 private:
  sf::Sprite sprite_;
  sf::Texture& texture_;

  enum Facing {
    down = 0,
    downLeft = 1,
    left = 2,
    upLeft = 3,
    up = 4,
    upRight = 5,
    right = 6,
    downRight = 7,
  };

  Facing dir_;
  sf::Vector2f player_size_;
  sf::Vector2f position_;

 public:
  Player(sf::Texture& texture, sf::Vector2f size);
  ~Player() = default;
  void Move(sf::Vector2f new_position);
  void Animate();
  void Draw(sf::RenderWindow &window) const;
  sf::Vector2f GetPosition() const;

};







#endif //WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
