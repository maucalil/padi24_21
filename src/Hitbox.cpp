#include "Hitbox.hpp"

Hitbox::Hitbox(sf::Sprite &sprite, bool centered)
  : sprite(sprite)
{
  size = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

  if (centered) {
    position = sf::Vector2f(sprite.getOrigin().x - sprite.getGlobalBounds().width, sprite.getOrigin().y - sprite.getGlobalBounds().height);
  } else {
    position = sprite.getPosition();
  }

  hitbox.setOrigin(sprite.getOrigin());
  hitbox.setSize(size);
  hitbox.setPosition(position);
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

void Hitbox::rotate(const float& angle)
{
  hitbox.rotate(angle);
}

void Hitbox::update()
{
  hitbox.setPosition(sprite.getPosition());
}

void Hitbox::render(sf::RenderTarget *target)
{
  target->draw(hitbox);
}
