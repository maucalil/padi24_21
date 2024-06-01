#include "EnemySpawner.hpp"

EnemySpawner::EnemySpawner()
{
  timeToSpawn = 1;
  timer = 0.f;
  pos = sf::Vector2f(400, 0);
  
  shape.setSize(sf::Vector2f(50, 50));
  shape.setPosition(pos);
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update(const float dt, const sf::Vector2f playerPos)
{
  timer += dt;
  if (timer >= timeToSpawn && enemies.size() < 1) {
    Enemy enemy = Enemy(pos);
    enemies.push_back(enemy);

    timer = 0;
  }
  // std::cout << "Enemy count: " << enemies.size() << "\n";

  for (size_t i = 0; i < enemies.size(); i++) {
    enemies[i].update(dt, playerPos);
  }
}

void EnemySpawner::render(sf::RenderTarget *target)
{
  target->draw(shape);

  for (size_t i = 0; i < enemies.size(); i++) {
    enemies[i].render(target);
  }
}
