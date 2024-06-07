#include "EnemySpawner.hpp"

EnemySpawner::EnemySpawner()
{
  timeToSpawn = 0.25f;
  timer = 0.f;
  pos = sf::Vector2f(200, 200);

  shape.setSize(sf::Vector2f(64, 64));
  shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
  shape.setPosition(pos);
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update(const float dt, std::vector<Enemy *> &enemies)
{
  timer += dt;
  if (timer >= timeToSpawn && enemies.size() < 5)
  {
    enemies.push_back(new Enemy(pos));

    timer = 0;
  }
}

void EnemySpawner::render(sf::RenderTarget &target)
{
  target.draw(shape);
}
