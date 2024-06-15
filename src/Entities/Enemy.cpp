#include "Entities/Enemy.hpp"

void Enemy::initVariables()
{
  damage = Constants::DefaultEnemyDamage;
  exp = Constants::DefaultEnemyExp;
  health = Constants::DefaultEnemyHealth;
  movSpeed = Constants::DefaultEnemyMovSpeed;
}

Enemy::Enemy(sf::Vector2f pos)
{
  initVariables();

  sprite.setTexture(*ResourceManager::getTexture("enemy/enemy.png"));
  sprite.setTextureRect(sf::IntRect(0, 0, 241, 222));
  sprite.setOrigin(getCenter());
  sprite.setPosition(pos);
  sprite.scale(sf::Vector2f(.3f, .3f));
}

Enemy::~Enemy()
{
}

void Enemy::handleBulletHit(const int &damage)
{
  health -= damage;
}

int Enemy::getExp()
{
  return exp;
}

void Enemy::update(const float dt, const sf::Vector2f target)
{
  lastValidPosition = getPosition();
  sf::Vector2f direction = Utils::NormalizeVector(target - sprite.getPosition());
  move(dt, direction);

  float angle = Utils::GetAngle(direction);
  rotate(angle - sprite.getRotation());
}

void Enemy::render(sf::RenderTarget &target)
{
  target.draw(sprite);
}
