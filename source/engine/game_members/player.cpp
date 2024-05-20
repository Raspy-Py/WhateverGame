#include "player.h"


Player::Player(sf::Texture& texture, sf::Texture& projectile_texture, sf::Vector2f size)
    : GameObject(texture, size), projectile_texture_(projectile_texture) {

  sprite_.setOrigin({sprite_.getLocalBounds().width / 2,
                     sprite_.getLocalBounds().height / 2});
  sprite_.setScale({size.x / sprite_.getLocalBounds().width,
                    size.y / sprite_.getLocalBounds().height});
  sprite_.setPosition(position_);
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




void Player::Shoot(float speed) {
  sf::Vector2f barrel_position = position_ - sf::Vector2f{std::cos(direction_),
                                                          std::sin(direction_)} * object_size_.x;
    projectiles_.push_back(std::make_unique<Projectile>(projectile_texture_, barrel_position, direction_, speed));
  std::cout << "Shooting!" << std::endl;
  std::cout << "projectiles size: " << projectiles_.size() << std::endl;
}

void Player::Update(float dt, const std::vector<std::unique_ptr<GameObject>>& objects) {
  for (auto& proj : projectiles_) {
    if (proj->isExpired()) continue;
    proj->Update(dt, objects);
  }
    projectiles_.erase(std::remove_if(projectiles_.begin(), projectiles_.end(),
                                        [](const auto& proj) { return proj->isExpired(); }),
                        projectiles_.end());
}


void Player::Draw(sf::RenderWindow &window) const {
  window.draw(sprite_);
  for (const auto& proj : projectiles_) {
    if (!proj->isExpired()) {
      window.draw(proj->GetSprite());
    }
  }
}
