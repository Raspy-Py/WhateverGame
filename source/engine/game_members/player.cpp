#include "player.h"


Player::Player(sf::Texture& texture, sf::Vector2f size ):
    texture_(texture), sprite_(texture), dir_(down), player_size_(size) {

}

void Player::Draw(sf::RenderWindow &window) const {
  window.draw(sprite_);
}

void Player::Move(sf::Vector2f new_position) {
  sprite_.setPosition(new_position);

  if ( new_position.y >  position_.y ) {
    if ( new_position.x >  position_.x ) {
      dir_ = upRight;
    } else if ( new_position.x < position_.x ) {
      dir_ = upLeft;
    } else {
      dir_ = up;
    }
  } else if ( new_position.y >  position_.y ) {
    if ( new_position.x >  position_.x ) {
      dir_ = downRight;
    } else if ( new_position.x < position_.x ) {
      dir_ = downLeft;
    } else {
      dir_ = down;
    }
  } else {
    if ( new_position.x >  position_.x ) {
      dir_ = right;
    } else {
      dir_ = left;
    }
  }


  Animate();
}

void Player::Animate() {
  sf::Angle angle{-static_cast<float>( (M_PI/8) * static_cast<float>(dir_) )};
  sprite_.setRotation(angle);
}

sf::Vector2f Player::GetPosition() const {
  return sprite_.getPosition();
}