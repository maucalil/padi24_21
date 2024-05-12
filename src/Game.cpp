#include "Game.hpp"

// Private methods
void Game::initVariables()
{
  window = nullptr;
}

void Game::initWindow()
{
  windowSettings.antialiasingLevel = 8;
  window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Window", sf::Style::Close | sf::Style::Titlebar, windowSettings);
  window->setFramerateLimit(60);
}

// Constructor
Game::Game()
{
  initVariables();
  initWindow();
}

// Destructor
Game::~Game()
{
  delete window;
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
    case sf::Event::KeyPressed:
      if (event.key.code == sf::Keyboard::Escape)
        window->close();
      break;
    }
  }
}

// Public methods
void Game::update()
{
  updateEvents();
  player.update(window);
}

void Game::render()
{
  window->clear(sf::Color::Black);

  player.render(window);

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
