#pragma once
#include "SFML/Graphics.hpp"

class Player {
 public:
  Player() = default;
  Player(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& file);
  ~Player() = default;

  void moveRight();
  void setRectSize();
  void setRectPos();

  sf::RectangleShape *getShape();

 private:
  sf::RectangleShape rect_;
  sf::Texture texture_;
  sf::Vector2f size_;
  sf::Vector2f position_;
};