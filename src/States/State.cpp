#include "States/State.hpp"

 void State::changeState(State* newState)
{
  states->pop();
  states->push(newState);
}

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
