#include "System/Game.hpp"

// Private methods
void Game::initVariables()
{
  window = nullptr;
}

void Game::initWindow()
{
  windowSettings.antialiasingLevel = 8;
  window = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML Window", sf::Style::Close | sf::Style::Titlebar, windowSettings);
  window->setFramerateLimit(60);
}

void Game::initStates()
{
  states.push(new GameState(window));
}

// Constructor
Game::Game()
{
  initVariables();
  initWindow();
  initStates();
}

// Destructor
Game::~Game()
{
  delete window;

  while (!states.empty())
  {
    delete states.top();
    states.pop();
  }
}

void Game::updateEvents()
{
  while (window->pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      window->close();
      break;
    }
  }
}

// Public methods
void Game::update()
{
  updateEvents();

  if(!states.empty()) {
    states.top()->update(dt);

    if (states.top()->getQuit()) {
      delete states.top();
      states.pop();
    }
  } else {
    window->close();
  }
}

void Game::render()
{
  window->clear(sf::Color::Black);

  if(!states.empty())
    states.top()->render(window);

  window->display();
}

void Game::run()
{
  while (window->isOpen())
  {
    // update delta time with the time it takes to update and render one frame
    dt = dtClock.restart().asSeconds();
    update();
    render();
  }
}
