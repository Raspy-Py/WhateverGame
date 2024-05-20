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




void Player::Shoot(float speed) {
  sf::Vector2f barrel_position = position_ - sf::Vector2f{std::cos(direction_),
                                                          std::sin(direction_)} * player_size_.x;
  Projectile newProjectile(projectile_texture_, barrel_position, direction_, speed);
  projectiles_.push_back(newProjectile);
  std::cout << "Shooting!" << std::endl;
  std::cout << "projectiles size: " << projectiles_.size() << std::endl;
}

void Player::Update(float dt) {
  for (auto& proj : projectiles_) {
    proj.Update(dt);
  }
}

void Player::UpdateProjectiles(float dt) {
  for (auto& proj : projectiles_) {
    proj.Update(dt);
  }
  projectiles_.erase(std::remove_if(projectiles_.begin(), projectiles_.end(),
                                    [](const Projectile& p) { return p.isExpired(); }), projectiles_.end());
}

void Player::DrawProjectiles(sf::RenderWindow &window) {
  for (auto& proj : projectiles_) {
    proj.Draw(window);
  }
}

void Player::CheckProjectileCollisions(const std::vector<Projectile>& projectiles) {
  for (const auto& projectile : projectiles) {
    if (projectile.checkCollision(sprite_)) {
      Die(dead_texture_);
      break;
    }
  }
}