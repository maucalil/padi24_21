#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.hpp"
/*
  Wrapper class
*/
class Game
{
private:
  // Variables
  sf::RenderWindow *window;
  sf::ContextSettings windowSettings;
  sf::Event event;

  // Delta time
  sf::Clock dtClock;
  float dt;

  Player player;

  // Methods
  void initVariables();
  void initWindow();

public:
  Game();
  virtual ~Game();

  // Methods
  void updateEvents();
  void update();
  void render();
  void run();
};

#endif