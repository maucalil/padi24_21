#include "Entities/Entity.hpp"

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

void Entity::rotate(const float &angle)
{
  sprite.rotate(angle);
  hitbox->rotate(angle);
}

Hitbox& Entity::getHitbox()
{
  return *hitbox;
}

sf::Vector2f Entity::getPosition()
{
  return sprite.getPosition();
}

sf::Vector2f Entity::getCenter()
{
  sf::FloatRect spriteBounds = sprite.getGlobalBounds();
  sf::Vector2f spritePos = getPosition();
  return sf::Vector2f(spritePos.x + spriteBounds.width / 2, spritePos.y + spriteBounds.height / 2);
}

int Entity::getHealth()
{
  return health;
}

int Entity::getMaxHealth()
{
  return maxHealth;
}

bool Entity::isDead()
{
  return health <= 0;
}
