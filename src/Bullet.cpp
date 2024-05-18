#include "Bullet.hpp"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& target, float speed)
{
  shape.setRadius(5);
  shape.setPosition(position);
  direction = Utils::NormalizeVector(target - position);
  this->speed = speed;
}

void Bullet::update(const float dt)
{
  shape.setPosition(shape.getPosition() + direction * speed * dt);
}

void Bullet::render(sf::RenderTarget *target)
{
  target->draw(shape);
}
