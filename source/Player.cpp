#include "Player.hpp"
#include <iostream>

Player::Player(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& file)
    : size_(size.x, size.y), position_(pos.x, pos.y) {
  if (!texture_.loadFromFile(file))
    std::cerr << "Error: failed to load texture [" << file << "]. " << std::endl;
  rect_.setTexture(&texture_);
  setRectSize();
  setRectPos();
}

void Player::setRectSize() {
  rect_.setSize(size_);
}

void Player::setRectPos() {
  rect_.setPosition(position_);
}

sf::RectangleShape* Player::getShape() {
  return &rect_;
}

void Player::moveRight() {
  position_.x += 1;
  rect_.setPosition({position_.x + 1, position_.y});
}