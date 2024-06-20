#include "Entities/Enemy.hpp"

void Enemy::initVariables()
{
  attackSpeed = Constants::DefaultEnemyAttackSpeed;
  damage = Constants::DefaultEnemyDamage;
  exp = Constants::DefaultEnemyExp;
  health = Constants::DefaultEnemyHealth;
  movSpeed = Constants::DefaultEnemyMovSpeed;
}

void Enemy::initAnimations()
{
  Animation *moveAnimation = new Animation(sprite, sf::Vector2u(Constants::EnemyMoveTextureWidth, Constants::EnemyMoveTextureHeight),
                                           sf::Vector2u(Constants::EnemyMoveFrameWidth, Constants::EnemyMoveFrameHeight),
                                           Constants::EnemyMoveNumFrames,
                                           Constants::EnemyMoveTimePerFrame);
  moveAnimation->setRepeat(true);
  animations[EnemyState::MOVING] = moveAnimation;

  Animation *attackAnimation = new Animation(sprite, sf::Vector2u(Constants::EnemyAttackTextureWidth, Constants::EnemyAttackTextureHeight),
                                             sf::Vector2u(Constants::EnemyAttackFrameWidth, Constants::EnemyAttackFrameHeight),
                                             Constants::EnemyAttackNumFrames,
                                             Constants::EnemyAttackTimePerFrame);
  attackAnimation->setRepeat(true);
  animations[EnemyState::ATTACKING] = attackAnimation;

  sprite.setTexture(*ResourceManager::getTexture("enemy/enemy_move.png"));
  changeAnimation(*animations[EnemyState::MOVING]);
}

void Enemy::updateAnimation()
{
  if (enemyState == ATTACKING && !(lastState == ATTACKING))
  {
      sprite.setTexture(*ResourceManager::getTexture("enemy/enemy_attack.png"));
      changeAnimation(*animations[EnemyState::ATTACKING]);
  }
  else if (enemyState == MOVING && !(lastState == MOVING))
  {
      sprite.setTexture(*ResourceManager::getTexture("enemy/enemy_move.png"));
      changeAnimation(*animations[EnemyState::MOVING]);
  }
}

void Enemy::changeState(EnemyState state)
{
  lastState = enemyState;
  enemyState = state;
}

Enemy::Enemy(sf::Vector2f pos)
{
  initVariables();
  initAnimations();

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

int Enemy::getDamage()
{
  return damage;
}

bool Enemy::haveAttacked()
{
  return attacked;
}

void Enemy::setIsAttacking(bool isAttacking)
{
  this->isAttacking = isAttacking;
}

void Enemy::update(const float dt, const sf::Vector2f target)
{
  lastValidPosition = getPosition();
  sf::Vector2f direction = Utils::NormalizeVector(target - sprite.getPosition());
  move(dt, direction);

  float angle = Utils::GetAngle(direction);
  rotate(angle - sprite.getRotation());

  if (isAttacking && attackTimer.getElapsedTime().asSeconds() >= attackSpeed)
  {
    isAttacking = false;
    attackTimer.restart();
    attacked = true;
  } else {
    attacked = false;
  }

  if (isAttacking)
    changeState(EnemyState::ATTACKING);
  else
    changeState(EnemyState::MOVING);

  updateAnimation();
  currentAnimation->update(dt);
}

void Enemy::render(sf::RenderTarget &target)
{
  target.draw(sprite);
  sf::Text text;
  text.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
  text.setString(std::to_string(enemyState));
  target.draw(text);
}
