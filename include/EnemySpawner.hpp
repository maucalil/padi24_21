#ifndef ENEMYSPAWNER_HPP
#define ENEMYSPAWNER_HPP

#include "Entities/Enemy.hpp"
#include "Constants.hpp"
#include <cstdlib>

class EnemySpawner
{
private:
  sf::Vector2f pos;

  float timeToSpawn;
  float timer;
  unsigned maxNumberEnemies;

public:
  EnemySpawner();
  ~EnemySpawner();

  void update(const float dt, std::vector<Enemy *> &enemies);
};

#endif