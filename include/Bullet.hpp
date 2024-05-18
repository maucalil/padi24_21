#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"
#include "Utils.hpp"

class Bullet
{
private:
  float speed;
  sf::Vector2f direction;
  sf::CircleShape shape;

public:
  Bullet(const sf::Vector2f& position, const sf::Vector2f& target, float speed);
	void update(const float dt);
  void render(sf::RenderTarget* target);
};

#endif