#include "EnemySpawner.hpp"

EnemySpawner::EnemySpawner()
{
  srand(time(0));
  timeToSpawn = 0.25f;
  timer = 0.f;

  wave = 1;
  waveNumEnemies = Constants::DefaultWaveNumEnemies;
  remainingEnemies = Constants::DefaultWaveNumEnemies;
  numEnemiesSpawned = 0;
  canSpawn = false;
}

EnemySpawner::~EnemySpawner()
{
}

unsigned EnemySpawner::getWave()
{
  return wave;
}

unsigned EnemySpawner::getWaveNumEnemies()
{
  return waveNumEnemies;
}

unsigned EnemySpawner::getRemainingEnemies()
{
  return remainingEnemies;
}

bool EnemySpawner::isSpawning()
{
  return canSpawn;
}

void EnemySpawner::startSpawning()
{
  canSpawn = true;
}

void EnemySpawner::handleEnemyKilled()
{
  remainingEnemies--;
}

void EnemySpawner::update(const float dt, std::vector<Enemy *> &enemies)
{
  timer += dt;
  if (canSpawn && timer >= timeToSpawn && numEnemiesSpawned < waveNumEnemies)
  {
    sf::Vector2f pos = Constants::GetEnemySpawnPosition(rand() % Constants::NumPossibleEnemyPos);
    enemies.push_back(new Enemy(pos));

    numEnemiesSpawned++;
    timer = 0;
  } else if (numEnemiesSpawned == waveNumEnemies && enemies.size() == 0) {
    wave++;
    waveNumEnemies += 5;
    remainingEnemies = waveNumEnemies;
    numEnemiesSpawned = 0;
    canSpawn = false;
  }
}