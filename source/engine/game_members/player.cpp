#include "player.h"


Player::Player(sf::Texture& texture, sf::Vector2f size ): GameObject(texture, size) {}


void Player::Move(float distance) {
  position_ += {
    std::cos(direction_) * speed_ * distance,
    std::sin(direction_) * speed_ * distance
  };

  Animate();
}

void Player::Rotate(float radians){
  direction_ += radians * rotation_speed_;
  Animate();
}




