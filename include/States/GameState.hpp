#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "States/State.hpp"
#include "Entities/Player.hpp"
#include "EnemySpawner.hpp"
#include "GUI/Button.hpp"

class GameState : public State
{
private:
  Player* player;
  EnemySpawner* enemySpawner;
  std::vector<Enemy*> enemies;
  std::vector<Bullet*> bullets;

  sf::Sprite ground;

  void initEntities();

public:
  GameState(sf::RenderWindow* window);
  ~GameState();

  bool checkWindowCollision(Entity& entity);
  bool didPlayerCollide();
  bool didEnemyCollide(Enemy* enemy, int enemyId);
  bool didBulletCollide(Bullet& bullet);


  void handleEvent(const sf::Event &event);
  void update(const float dt);
  void render(sf::RenderTarget* target);
};

#endif