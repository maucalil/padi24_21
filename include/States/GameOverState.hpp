#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "GUI/Button.hpp"
#include "States/State.hpp"
#include "States/MainMenuState.hpp"

class GameOverState : public State
{
private:
  sf::RectangleShape background;
  sf::Text mainText;
  sf::Text infoText;

public:
  GameOverState(sf::RenderWindow *window, std::stack<State *> *states);
  ~GameOverState();


  void handleEvent(const sf::Event &event);
  void update(const float dt);
  void render(sf::RenderTarget &target);
};
  
#endif