#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Player.hpp"
#include "EnemySpawner.hpp"

class GameState : public State
{
private:
  Player* player;
  EnemySpawner* enemySpawner;
  std::vector<Enemy*> enemies;
  std::vector<Bullet*> bullets;

  void initEntities();

public:
  GameState(sf::RenderWindow* window);
  ~GameState();

  bool checkWindowCollision(Entity& entity);
  bool didPlayerCollide();
  bool didEnemyCollide(Enemy* enemy, int enemyId);
  bool didBulletCollide(Bullet& bullet);

  void updateInput();
  void update(const float dt);
  void render(sf::RenderTarget* target);
};

#endif