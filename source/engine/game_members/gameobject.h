#ifndef WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_GAMEOBJECT_H_
#define WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_GAMEOBJECT_H_

#include <SFML/Graphics.hpp>
#include <cmath>

class GameObject {
 public:
  GameObject(sf::Texture &texture, sf::Vector2f size);
  virtual ~GameObject() = default;


  virtual void Animate();
  virtual void Draw(sf::RenderWindow &window) const;

  sf::Vector2f GetPosition() const { return position_; }
  float GetDirection() const { return direction_; }
  void SetDirection(float direction);
  void SetPosition(const sf::Vector2f& position);
  void SetSpeed(float speed) { speed_ = speed; }

  sf::Sprite GetSprite() const { return sprite_; }

  bool Intersect(const GameObject& other);

 protected:
  sf::Sprite sprite_;
  sf::Texture &texture_;
  float direction_;
  float speed_;
  sf::Vector2f position_;
  sf::Vector2f object_size_;
};

#endif // WHATEVERGAME_SOURCE_ENGINE_GAME_MEMBERS_GAMEOBJECT_H_
