#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entities/Entity.hpp"

class Bullet : public Entity
{
private:
  sf::Vector2f direction;

public:
  Bullet(const sf::Vector2f &position, const sf::Vector2f &dir, float speed);
  ~Bullet();

  void update(const float dt);
  void render(sf::RenderTarget &target);
};

#endif