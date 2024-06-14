#include "EnemySpawner.hpp"

EnemySpawner::EnemySpawner()
{
  srand(time(0));
  timeToSpawn = 0.25f;
  timer = 0.f;
  maxNumberEnemies = 15;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update(const float dt, std::vector<Enemy *> &enemies)
{
  timer += dt;
  if (timer >= timeToSpawn && enemies.size() < maxNumberEnemies)
  {
    sf::Vector2f pos = Constants::GetEnemySpawnPosition(rand() % Constants::NumPossibleEnemyPos);
    enemies.push_back(new Enemy(pos));

    timer = 0;
  }
}