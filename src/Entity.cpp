#include "Entity.hpp"

void Entity::update(const float dt, sf::Window *window)
{
}

void Entity::move(const float dt, const sf::Vector2f &dir)
{
  this->sprite.move(dir * dt * movSpeed);
}

void Entity::createHitbox()
{
  hitbox = new Hitbox(sprite);
}

void Entity::handleCollision()
{
  sprite.setPosition(lastValidPosition);
}

Hitbox& Entity::getHitbox()
{
  return *hitbox;
}

sf::Vector2f Entity::getPosition()
{
  return sprite.getPosition();
}

int Entity::getHealth()
{
  return health;
}
