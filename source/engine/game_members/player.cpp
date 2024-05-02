#include "player.h"


Player::Player(sf::Texture& texture, sf::Vector2f size ):
    texture_(texture), sprite_(texture), player_size_(size) {
  sprite_.setScale({
    size.y / sprite_.getLocalBounds().height,
    size.x / sprite_.getLocalBounds().width
  });


  direction_ = 0.0f;
  position_ = {0, 0};
  Animate();
}

void Player::Draw(sf::RenderWindow &window) const {
  window.draw(sprite_);
}

void Player::Move(float distance) {
  position_ += {
    std::cos(direction_) * speed_,
    std::sin(direction_) * speed_
  };

  Animate();
}

void Player::Rotate(float radians){
  direction_ += radians;
  Animate();
}


void Player::Animate() {
  sprite_.setRotation(sf::degrees(direction_));
  sprite_.setPosition(position_);
}

