#include "Enemy.hpp"

void Enemy::initVariables()
{
  movSpeed = 100.f;
  health = 10;
}

Enemy::Enemy(sf::Vector2f pos)
{
  initVariables();

  sprite.setTexture(*ResourceManager::getTexture("enemy/monsters.png"));
  sprite.setPosition(pos);
  sprite.setTextureRect(sf::IntRect(96, 128, 32, 32));
  sprite.scale(sf::Vector2f(2.f, 2.f));

  createHitbox();

  std::cout << "Created Enemy\n";

}

Enemy::~Enemy()
{
  std::cout << "Destroyed Enemy\n";
}

void Enemy::handleBulletHit(const int &damage)
{
  health -= damage;
}

void Enemy::update(const float dt, const sf::Vector2f target)
{
  lastValidPosition = getPosition();
  sf::Vector2f direction = Utils::NormalizeVector(target - sprite.getPosition());
  move(dt, direction);
  hitbox->update();
}

void Enemy::render(sf::RenderTarget *target)
{
  target->draw(sprite);
  hitbox->render(target);
}
