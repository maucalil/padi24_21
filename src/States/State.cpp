#include "States/State.hpp"

State::State(sf::RenderWindow *window, std::stack<State *> *states)
{
  this->window = window;
  this->states = states;
  quit = false;
}

State::~State()
{
}

const bool &State::getQuit() const
{
  return quit;
}
