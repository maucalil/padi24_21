#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Utils.hpp"
#include "ResourceManager.hpp"

#define DEFAULT_DAMAGE 10
#define DEFAULT_HEALTH 20
#define DEFAULT_EXP 5
#define DEFAULT_MOV_SPEED 100.f

class Enemy : public Entity
{
private:
  int exp; // how much experience it is worth when killed 
  void initVariables();

  void updateEnemyPosition();

public:
  Enemy(sf::Vector2f pos);
  ~Enemy();

  void handleBulletHit(const int& damage);
  int getExp();

	void update(const float dt, const sf::Vector2f target);
  void render(sf::RenderTarget* target);
};

#endif