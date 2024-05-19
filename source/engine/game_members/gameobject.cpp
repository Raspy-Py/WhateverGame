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

float GameObject::Intersect(const GameObject& other, float distance) {
  sf::Vector2f new_position_ = {
      std::cos(direction_) * speed_ * distance,
      std::sin(direction_) * speed_ * distance
  };

  new_position_ += position_;
  sprite_.setPosition(new_position_);

  if ( sprite_.getGlobalBounds().findIntersection( other.GetSprite().getGlobalBounds()).has_value() ) {
    auto intersection = *sprite_.getGlobalBounds().findIntersection( other.GetSprite().getGlobalBounds() );
    return intersection.getSize().x * intersection.getSize().y;
  }
  sprite_.setPosition(position_);

  return 0.0f;
}

void GameObject::Animate() {
  sprite_.setRotation(sf::radians(direction_ - 3.14159f / 2.0f));
  sprite_.setPosition(position_);
}