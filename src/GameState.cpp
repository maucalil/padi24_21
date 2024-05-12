#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window)
  : State(window)
{
  std::cout << "Created GameState\n";
}

GameState::~GameState()
{
  std::cout << "GameState ended!\n";
}

void GameState::updateKeyBinds()
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    _quit = true;
}

void GameState::update(const float &dt)
{
  updateKeyBinds();
}

void GameState::render(sf::RenderTarget* target)
{
}
