#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile {
public:
  Projectile(sf::Texture& texture, sf::Vector2f position, float direction, float speed);

  void Update(float dt);
  void Draw(sf::RenderWindow& window);
  bool isExpired() const;
  bool checkCollision(const sf::Sprite& target) const;

private:
    sf::Sprite sprite_;
    float speed_;
    float direction_;
    bool expired_ = false;
    sf::Vector2f position_;
};

#endif
