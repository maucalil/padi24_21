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

  Player player;

  // Methods
  void initVariables();
  void initWindow();

public:
  Game();
  virtual ~Game();

  // Methods
  const bool isRunning();
  void updateEvents();
  void update();
  void render();
};

#endif