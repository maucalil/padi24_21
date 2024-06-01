#include "Entity.hpp"

Entity::Entity()
{
  movSpeed = 10.f;
  health = 100;
}

Entity::~Entity()
{
}

void Entity::createSprite(sf::Texture* texture)
{
  sprite.setTexture(*texture);
}

void Entity::update(const float dt, sf::Window *window)
{
}

void Entity::move(const float dt, const sf::Vector2f &dir)
{
  this->sprite.move(dir * dt * movSpeed);
}
