#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "EnemySpawner.hpp"
// #include "Entities/Player.hpp"
#include "GUI/Button.hpp"
#include "GUI/PlayerGUI.hpp"
#include "States/State.hpp"
#include "World/Map.hpp"
#include "System/Collision.hpp"

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
  sf::Text waveInfo;

  std::string getWaveText();

  void initEntities();
  void initGUI();

public:
  GameState(sf::RenderWindow *window, std::stack<State *> *states);
  ~GameState();

  bool checkWindowCollision(const sf::Sprite &sprite);
  bool didPlayerCollide();
  bool didEnemyCollide(Enemy *enemy, int enemyId);
  bool didBulletCollide(Bullet &bullet);

  void handleEvent(const sf::Event &event);
  void update(const float dt);
  void render(sf::RenderTarget &target);
};

#endif