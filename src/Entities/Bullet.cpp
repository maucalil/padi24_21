#include "Entities/Bullet.hpp"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& dir, float speed)
{
  sprite.setTexture(*ResourceManager::getTexture("player/bullet.png"));
  sprite.setTextureRect(sf::IntRect(28, 52, 166, 35));
  sprite.setOrigin(getCenter());
  sprite.setPosition(position);
  sprite.scale(sf::Vector2f(0.3f, 0.3f));
  createHitbox();
  
  direction = dir;
  movSpeed = speed;

  rotate(Utils::GetAngle(direction));
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
