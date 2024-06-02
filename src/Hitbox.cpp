#include "Hitbox.hpp"

Hitbox::Hitbox(sf::Sprite &sprite)
  : sprite(sprite)
{
  offset = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

  hitbox.setSize(offset);
  hitbox.setPosition(sprite.getPosition());
  hitbox.setFillColor(sf::Color::Transparent);
  hitbox.setOutlineColor(sf::Color::Green);
  hitbox.setOutlineThickness(1.f);
}

sf::FloatRect Hitbox::getHitboxBounds()
{
  return hitbox.getGlobalBounds();
}

bool Hitbox::checkCollision(const sf::FloatRect &frect)
{
  return hitbox.getGlobalBounds().intersects(frect);
}

void Hitbox::update()
{
  hitbox.setPosition(sprite.getPosition());
}

void Hitbox::render(sf::RenderTarget *target)
{
  target->draw(hitbox);
}
