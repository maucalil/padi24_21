#ifndef GAME_HPP
#define GAME_HPP

#include "GameState.hpp"

/*
  Wrapper class
*/
class Game
{
private:
  // Variables
  sf::RenderWindow* window;
  sf::ContextSettings windowSettings;
  sf::Event event;

  // Delta time
  sf::Clock dtClock;
  float dt;

  std::stack<State*> states;

  // Methods
  void initVariables();
  void initWindow();
  void initStates();

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