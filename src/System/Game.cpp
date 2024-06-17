#include "System/Game.hpp"

// Private methods
void Game::initVariables()
{
  window = nullptr;
}

void Game::initWindow()
{
  windowSettings.antialiasingLevel = 8;
  // window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML Window", sf::Style::Close | sf::Style::Titlebar, windowSettings);
  window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "SFML Window", sf::Style::Fullscreen, windowSettings);
  window->setFramerateLimit(60);
}

void Game::initStates()
{
  states.push(new MainMenuState(window, &states));
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
    if (event.type == sf::Event::Closed)
    {
      window->close();
    }
    else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
    {
      window->close();
    }
    else
    {
      states.top()->handleEvent(event);
    }
  }
}

// Public methods
void Game::update()
{
  updateEvents();

  if (!states.empty())
  {
    states.top()->update(dt);

    if (states.top()->getQuit())
    {
      delete states.top();
      states.pop();
    }
  }
  else
  {
    window->close();
  }
}

void Game::render()
{
  window->clear(sf::Color::Black);

  if (!states.empty())
    states.top()->render(*window);

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
