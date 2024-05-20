#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "projectile.h"

class Player {
 public:
  Player(sf::Texture& texture,sf::Texture& dead_texture, sf::Texture& projectile_texture, sf::Vector2f size);
  ~Player() = default;
  void Move(float distance);
  void Rotate(float radians);
  void Animate();
  void Draw(sf::RenderWindow &window) const;
  void Shoot(float speed);
  void Update(float dt);
  void UpdateProjectiles(float dt);
  void DrawProjectiles(sf::RenderWindow& window);
  void CheckProjectileCollisions(const std::vector<Projectile>& projectiles);

  sf::Vector2f GetPosition() const {return position_; }
  float GetDirection() const { return direction_; }
  void SetDirection(float direction) { direction_ = direction; Animate(); }
  void SetPosition(const sf::Vector2f& position) {position_ = position; Animate(); }
  void Die(sf::Texture& texture_die) { sprite_.setTexture(texture_die); alive_ = false; }
  bool isAlive() const { return alive_; }
  std::vector<Projectile>& GetProjectiles() { return projectiles_; }

 private:
  sf::Sprite sprite_;
  sf::Texture &texture_;
  sf::Texture &projectile_texture_;
  sf::Texture &dead_texture_;
  bool alive_ = true;

  float speed_ = 200.f;
  float rotation_speed_ = 1.f;
  float direction_;
  sf::Vector2f position_;
  sf::Vector2f player_size_;
  std::vector<Projectile> projectiles_;
};







#endif //WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_PLAYER_H_
