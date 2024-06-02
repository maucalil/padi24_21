#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Utils.hpp"
#include "ResourceManager.hpp"

class Enemy : public Entity
{
private:
  void initVariables();

  void updateEnemyPosition();

public:
  Enemy(sf::Vector2f pos);
  ~Enemy();

  void handleBulletHit(const int& damage);

	void update(const float dt, const sf::Vector2f target);
  void render(sf::RenderTarget* target);
};

#endif