#include "Enemy.hpp"

void Enemy::initVariables()
{
  movSpeed = 100.f;
}

Enemy::Enemy(sf::Vector2f pos)
{
  initVariables();

  sprite.setTexture(*ResourceManager::getTexture("enemy/enemy_spritesheet.png"));
  sprite.setPosition(pos);
  sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

  std::cout << "Created Enemy\n";

}

Enemy::~Enemy()
{
  std::cout << "Destroyed Enemy\n";
}

void Enemy::update(const float dt, const sf::Vector2f target)
{
  sf::Vector2f direction = Utils::NormalizeVector(target - sprite.getPosition());
  sprite.setPosition(sprite.getPosition() + direction * movSpeed * dt);
}

void Enemy::render(sf::RenderTarget *target)
{
  target->draw(sprite);
}
