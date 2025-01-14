#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entities/Entity.hpp"
#include "System/Animation.hpp"

class Enemy : public Entity
{
private:
  enum EnemyState
  {
    MOVING,
    ATTACKING,
  };
  EnemyState enemyState;
  EnemyState lastState;
  bool isAttacking;
  bool attacked;

  std::map<EnemyState, Animation*> animations;
  Animation* animation;

  int exp; // how much experience it is worth when killed
  int damage;
  
  float attackSpeed;
  sf::Clock attackTimer;

  sf::Sound growlSound;
  
  void initVariables();
  void initAnimations();

  void updateAnimation();

  void changeState(EnemyState state);

public:
  Enemy(sf::Vector2f pos, int waveLevel);
  ~Enemy();

  void handleBulletHit(const int &damage);
  int getExp();
  int getDamage();
  bool haveAttacked();
  void setIsAttacking(bool isAttacking);

  void update(const float dt, const sf::Vector2f target);
  void render(sf::RenderTarget &target);
};

#endif