#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entities/Entity.hpp"

class Enemy : public Entity
{
private:
  int exp; // how much experience it is worth when killed
  int damage;
  
  float attackSpeed;
  sf::Clock attackTimer;
  
  void initVariables();

  void updateEnemyPosition();

public:
  Enemy(sf::Vector2f pos);
  ~Enemy();

  void handleBulletHit(const int &damage);
  int getExp();
  int getDamage();
  bool haveAttacked();

  void update(const float dt, const sf::Vector2f target);
  void render(sf::RenderTarget &target);
};

#endif