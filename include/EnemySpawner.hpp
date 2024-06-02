#ifndef ENEMYSPAWNER_HPP
#define ENEMYSPAWNER_HPP

#include "Enemy.hpp"

class EnemySpawner
{
private:
  sf::Vector2f pos;
  sf::RectangleShape shape;

  float timeToSpawn;
  float timer;

public:
  EnemySpawner();
  ~EnemySpawner();

	void update(const float dt, std::vector<Enemy*>& enemies);
  void render(sf::RenderTarget* target);
};

#endif