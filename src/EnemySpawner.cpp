#include "EnemySpawner.hpp"

EnemySpawner::EnemySpawner()
{
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

void EnemySpawner::update(const float dt, std::vector<Enemy *> &enemies, sf::Vector2f pos)
{
  timer += dt;
  if (canSpawn && timer >= timeToSpawn && numEnemiesSpawned < waveNumEnemies)
  {
    enemies.push_back(new Enemy(pos, wave));

    numEnemiesSpawned++;
    timer = 0;
  } else if (numEnemiesSpawned == waveNumEnemies && enemies.size() == 0) {
    wave++;
    waveNumEnemies = ceil(waveNumEnemies * 1.06);
    remainingEnemies = waveNumEnemies;
    numEnemiesSpawned = 0;
    canSpawn = false;
  }
}