#ifndef ENEMYSPAWNER_HPP
#define ENEMYSPAWNER_HPP

#include "Enemy.hpp"

class EnemySpawner
{
private:
  sf::Vector2f pos;
  sf::RectangleShape shape;

  int timeToSpawn;
  float timer;

  std::vector<Enemy> enemies;

public:
  EnemySpawner();
  ~EnemySpawner();

	void update(const float dt, const sf::Vector2f playerPos);
  void render(sf::RenderTarget* target);
};

#endif