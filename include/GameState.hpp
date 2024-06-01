#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "EnemySpawner.hpp"

class GameState : public State
{
private:
  Player* player;
  EnemySpawner* enemySpawner;

  void initEntities();

public:
  GameState(sf::RenderWindow* window);
  ~GameState();

  void updateInput();
  void update(const float dt);
  void render(sf::RenderTarget* target);
};

#endif