#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>
#include "System/ResourceManager.hpp"

class State
{
protected:
  sf::RenderWindow *window;
  std::stack<State *> *states;
  bool quit;

  void changeState(State* newState);

public:
  State(sf::RenderWindow *window, std::stack<State *> *states);
  virtual ~State();

  const bool &getQuit() const;

  virtual void handleEvent(const sf::Event &event) = 0;
  virtual void update(const float dt) = 0;
  virtual void render(sf::RenderTarget &target) = 0;
};

#endif