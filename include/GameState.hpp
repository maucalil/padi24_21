#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Player.hpp"

class GameState : public State
{
private:
  Player* player;

  void initTextures();
  void initEntities();

public:
  GameState(sf::RenderWindow* window);
  ~GameState();

  void updateInput();
  void update(const float dt);
  void render(sf::RenderTarget* target);
};

#endif