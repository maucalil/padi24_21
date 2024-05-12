#include "State.hpp"

State::State(sf::RenderWindow *window)
{
  _window = window;
  _quit = false;
}

State::~State()
{
}

const bool &State::getQuit() const
{
  return _quit;
}
