#include "player.h"


Player::Player(sf::Texture& texture, sf::Texture& dead_texture,sf::Texture& projectile_texture, sf::Vector2f size ):
    texture_(texture), dead_texture_(dead_texture), sprite_(texture), player_size_(size), projectile_texture_(projectile_texture) {
  sprite_.setScale({
    size.y / sprite_.getLocalBounds().height,
    size.x / sprite_.getLocalBounds().width
  });

  sprite_.setOrigin(sprite_.getLocalBounds().getCenter());

  direction_ = 0.f;
  position_ = {0, 0};
  Animate();
}
//
//Player::Player(std::array<sf::Texture *, 4>& textures, sf::Vector2f player_size) :
//    texture_(*textures[0]),
//    firing_texture_(*textures[1]),
//    dead_texture_(*textures[2]),
//    projectile_texture_(*textures[3]),
//    player_size_(player_size) {
//    sprite_ = sf::Sprite(texture_);
//
//
//
//  sprite_.setScale({
//    player_size.y / sprite_.getLocalBounds().height,
//    player_size.x / sprite_.getLocalBounds().width
//  });
//
//  sprite_.setOrigin(sprite_.getLocalBounds().getCenter());
//
//  direction_ = 0.f;
//  position_ = {0, 0};
//  Animate();
//}

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