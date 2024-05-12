#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"

class GameState : public State
{
protected:

public:
  GameState(sf::RenderWindow* window);
  ~GameState();

  void updateKeyBinds();
  void update(const float& dt);
  void render(sf::RenderTarget* target);
};

#endif