#include "Bullet.hpp"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& target, float speed)
{
  sprite.setTexture(*ResourceManager::getTexture("player/bullet.png"));
  sprite.setTextureRect(sf::IntRect(148, 148, 24, 24));
  sprite.setPosition(position);
  
  direction = Utils::NormalizeVector(target - position);
  movSpeed = speed;

  createHitbox();
}

Bullet::~Bullet()
{
  delete hitbox;
}

void Bullet::update(const float dt)
{
  move(dt, direction);
  hitbox->update();
}

void Bullet::render(sf::RenderTarget *target)
{
  target->draw(sprite);
  hitbox->render(target);
}
