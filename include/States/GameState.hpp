#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "EnemySpawner.hpp"
// #include "Entities/Player.hpp"
#include "GUI/Button.hpp"
#include "GUI/PlayerGUI.hpp"
#include "States/State.hpp"
#include "World/Map.hpp"

class GameState : public State
{
private:
  Map *map;

  // Entities
  Player *player;
  EnemySpawner *enemySpawner;
  std::vector<Enemy *> enemies;
  std::vector<Bullet *> bullets;

  // GUI
  PlayerGUI *playerGUI;

  void initEntities();
  void initGUI();

public:
  GameState(sf::RenderWindow *window);
  ~GameState();

  bool checkWindowCollision(Entity &entity);
  bool didPlayerCollide();
  bool didEnemyCollide(Enemy *enemy, int enemyId);
  bool didBulletCollide(Bullet &bullet);

  void handleEvent(const sf::Event &event);
  void update(const float dt);
  void render(sf::RenderTarget &target);
};

#endif