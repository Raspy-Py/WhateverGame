#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "gameobject.h"

class Projectile : public GameObject {
public:
  Projectile(sf::Texture& texture, sf::Vector2f position, float direction, float speed);

  void Update(float dt, const std::vector<std::unique_ptr<GameObject>>& objects);
  bool isExpired() const;

private:
  bool expired_ = false;
};

#endif
