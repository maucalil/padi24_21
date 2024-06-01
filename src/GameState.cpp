#include "GameState.hpp"

void GameState::initEntities()
{
  player = new Player(sf::Vector2f(0, 0));
  enemySpawner = new EnemySpawner();
}

GameState::GameState(sf::RenderWindow *window)
    : State(window)
{
  initEntities();

  std::cout << "Created GameState\n";
}

GameState::~GameState()
{
  delete player;
  delete enemySpawner;
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
  enemySpawner->update(dt, player->getPosition());
}

void GameState::render(sf::RenderTarget *target)
{
  player->render(target);
  enemySpawner->render(target);
}
