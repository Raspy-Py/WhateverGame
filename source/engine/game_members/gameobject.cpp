#include "gameobject.h"
#include <iostream>
GameObject::GameObject(sf::Texture &texture, sf::Vector2f size)
    : texture_(texture), sprite_(texture), object_size_(size), direction_(0.f), speed_(0.f), position_{0, 0} {
  sprite_.setScale({
                       size.x / sprite_.getLocalBounds().width,
                       size.y / sprite_.getLocalBounds().height
                   });

  sprite_.setOrigin(sprite_.getLocalBounds().getCenter());

  direction_ = 0.f;
  position_ = {0, 0};
  Animate();
}

void GameObject::Draw(sf::RenderWindow &window) const {
  window.draw(sprite_);
}

void GameObject::SetDirection(float direction) {
  direction_ = direction;
  Animate();
}

void GameObject::SetPosition(const sf::Vector2f& position) {
  position_ = position;
  Animate();
}

bool GameObject::Intersect(const GameObject& other) {
  auto intersection = sprite_.getGlobalBounds().findIntersection
      ( other.GetSprite().getGlobalBounds());
  if (intersection.has_value()) {
    return intersection->width * intersection->height >10;
  }
  return false;
}

void GameObject::Animate() {
  sprite_.setRotation(sf::radians(direction_ - 3.14159f / 2.0f));
  sprite_.setPosition(position_);
}