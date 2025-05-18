#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_

#include "gameobject.h"
#include <iostream>
#include "projectile.h"

class Player : public GameObject {
 public:
  Player(sf::Texture &texture, sf::Texture &projectile_texture, sf::Vector2f size);
  ~Player() override = default;

  void Move(float distance);
  void Rotate(float radians);
  void Shoot(float speed);
  void Update(float dt, const std::vector<std::unique_ptr<GameObject>>& objects);
  void Draw(sf::RenderWindow &window)  const override;

  void Die(sf::Texture& texture_die) { sprite_.setTexture(texture_die); alive_ = false; }
  bool isAlive() const { return alive_; }
//  std::vector<Projectile&>& GetProjectiles() { return projectiles_; }
  std::vector<std::unique_ptr<Projectile>>& GetProjectiles() { return projectiles_; }
 private:
  sf::Texture &projectile_texture_;
  bool alive_ = true;
  float speed_ = 100.f;
  float rotation_speed_ = 1.f;
  std::vector<std::unique_ptr<Projectile>> projectiles_;
};







#endif //WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
