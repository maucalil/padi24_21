#include "Bullet.hpp"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& target, float speed)
{
  sprite.setTexture(*ResourceManager::getTexture("player/bullet.png"));
  sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
  sprite.scale(sf::Vector2f(0.5, 0.5));
  sprite.setPosition(position);
  
  direction = Utils::NormalizeVector(target - position);
  movSpeed = speed;

  createHitbox();

  std::cout << "Created Bullet\n";
}

Bullet::~Bullet()
{
  delete hitbox;
  std::cout << "Destroyed Bullet\n";
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
