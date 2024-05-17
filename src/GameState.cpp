#include "GameState.hpp"

void GameState::initTextures()
{
  if (!textures["PLAYER_IDLE"].loadFromFile("../resources/player/dark_soldier-original.png"))
  {
    throw "ERROR::GAME_STATE: Could not load player texture";
  }
}

void GameState::initEntities()
{
  player = new Player(sf::Vector2f(0, 0), &textures["PLAYER_IDLE"]);
}

GameState::GameState(sf::RenderWindow *window)
    : State(window)
{
  initTextures();
  initEntities();

  std::cout << "Created GameState\n";
}

GameState::~GameState()
{
  delete player;
  std::cout << "Destroyed GameState\n";
}

void GameState::updateInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    quit = true;
}

void GameState::update(const float dt)
{
  updateInput();
  player->update(dt, window);
}

void GameState::render(sf::RenderTarget *target)
{
  player->render(target);
}
