#include "player.h"


Player::Player(sf::Texture& texture, sf::Vector2f size ):
    texture_(texture), sprite_(texture), player_size_(size) {
  sprite_.setScale({
    size.y / sprite_.getLocalBounds().height,
    size.x / sprite_.getLocalBounds().width
  });

  sprite_.setOrigin(sprite_.getLocalBounds().getCenter());

  direction_ = 0.f;
  position_ = {0, 0};
  Animate();
}

void Player::Draw(sf::RenderWindow &window) const {
  window.draw(sprite_);
}

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


void Player::Animate() {
  sprite_.setRotation(sf::radians(direction_ - 3.14159f / 2.0f));
  sprite_.setPosition(position_);
}

