#include "projectile.h"
#include <cmath>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, float direction, float speed)
    : GameObject(texture, {30, 30}){
  SetPosition(position);
  SetDirection(direction);
  speed_ = speed;
  sprite_.setOrigin({sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2});
  sprite_.setPosition(position_);
  sprite_.setRotation(sf::radians(direction_ - 3.14159f / 2.0f));
  sprite_.setScale({30.f / sprite_.getLocalBounds().width, 30.f / sprite_.getLocalBounds().height});
}


void Projectile::Update(float dt, const std::vector<std::unique_ptr<GameObject>>& objects) {
  position_.x -= std::cos(direction_) * speed_ * dt;
  position_.y -= std::sin(direction_) * speed_ * dt;
  sprite_.setPosition(position_);

  if (position_.x < 0 || position_.x > 800 || position_.y < 0 || position_.y > 600) {
    expired_ = true;
  }

  for (const auto& obj : objects) {
    if (Intersect(*obj)) {
      expired_ = true;
      break;
    }
  }
}

bool Projectile::isExpired() const {
  return expired_;
}
