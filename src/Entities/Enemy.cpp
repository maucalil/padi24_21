#include "Entities/Enemy.hpp"

void Enemy::initVariables()
{
  movSpeed = DEFAULT_ENEMY_MOV_SPEED;
  health = DEFAULT_ENEMY_HEALTH;
  exp = DEFAULT_ENEMY_EXP;
}

Enemy::Enemy(sf::Vector2f pos)
{
  initVariables();

  sprite.setTexture(*ResourceManager::getTexture("enemy/enemy.png"));
  sprite.setTextureRect(sf::IntRect(0, 0, 241, 222));
  sprite.setOrigin(getCenter());
  sprite.setPosition(pos);
  sprite.scale(sf::Vector2f(.35f, .35f));

  createHitbox();
}

Enemy::~Enemy()
{
  delete hitbox;
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
  hitbox->update();
}

void Enemy::render(sf::RenderTarget *target)
{
  target->draw(sprite);
  hitbox->render(target);
}
