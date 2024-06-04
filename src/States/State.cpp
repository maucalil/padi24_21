#include "States/State.hpp"

State::State(sf::RenderWindow *window)
{
  this->window = window;
  quit = false;
}

State::~State()
{
}

const bool &State::getQuit() const
{
  return quit;
}
