#include "Entity.hpp"

Entity::Entity()
{
  movSpeed = 10.f;
}

Entity::~Entity()
{
}

void Entity::createSprite(sf::Texture* texture)
{
  sprite.setTexture(*texture);
}

void Entity::move(const float dt, const sf::Vector2f &dir)
{
  this->sprite.move(dir * dt * movSpeed);
}
