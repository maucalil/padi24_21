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

  unsigned wave;
  unsigned waveNumEnemies;
  unsigned numEnemiesSpawned;
  unsigned remainingEnemies;
  bool canSpawn;

public:
  EnemySpawner();
  ~EnemySpawner();

  unsigned getWave();
  unsigned getWaveNumEnemies();
  unsigned getRemainingEnemies();

  bool isSpawning();
  void startSpawning();
  void handleEnemyKilled();

  int goToWave(int waveNum);

  void update(const float dt, std::vector<Enemy *> &enemies, sf::Vector2f pos);
};

#endif