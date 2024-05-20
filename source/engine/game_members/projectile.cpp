#include "projectile.h"
#include <cmath>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, float direction, float speed)
    : sprite_(texture), position_(position), direction_(direction), speed_(speed) {
  sprite_.setOrigin({sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2});
  sprite_.setPosition(position_);
  sprite_.setRotation(sf::radians(direction_ - 3.14159f / 2.0f));
  sprite_.setScale({30.f / sprite_.getLocalBounds().width, 30.f / sprite_.getLocalBounds().height});
}

void Projectile::Update(float dt) {
  position_.x -= std::cos(direction_) * speed_ * dt;
  position_.y -= std::sin(direction_) * speed_ * dt;
  sprite_.setPosition(position_);

  if (position_.x < 0 || position_.x > 800 || position_.y < 0 || position_.y > 600) {
      expired_ = true;
  }
}

void Projectile::Draw(sf::RenderWindow& window) {
  window.draw(sprite_);
}

bool Projectile::isExpired() const {
  return expired_;
}

bool Projectile::checkCollision(const sf::Sprite& target) const {
    return sprite_.getGlobalBounds().left < target.getGlobalBounds().left + target.getGlobalBounds().width &&
             sprite_.getGlobalBounds().left + sprite_.getGlobalBounds().width > target.getGlobalBounds().left &&
             sprite_.getGlobalBounds().top < target.getGlobalBounds().top + target.getGlobalBounds().height &&
             sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().height > target.getGlobalBounds().top;

}