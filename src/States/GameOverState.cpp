#include "States/GameOverState.hpp"

GameOverState::GameOverState(sf::RenderWindow *window, std::stack<State *> *states)
  : State(window, states)
{
  sf::Vector2f windowSize = window->getView().getSize();
  background.setFillColor(sf::Color(0, 0, 0, 100));
  background.setSize(windowSize);

  mainText.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
  mainText.setFillColor(sf::Color(200, 0, 0, 230));
  mainText.setCharacterSize(50);
  mainText.setString("You died!");
  sf::FloatRect mainTextBounds = mainText.getGlobalBounds();
  mainText.setOrigin(mainTextBounds.left + mainTextBounds.width / 2, mainTextBounds.top + mainTextBounds.height / 2);
  mainText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 20.f);

  infoText.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
  infoText.setFillColor(sf::Color(200, 0, 0, 230));
  infoText.setCharacterSize(20);
  infoText.setString("Press ESC to return to the main menu");
  sf::FloatRect infoTextBounds = infoText.getGlobalBounds();
  infoText.setOrigin(infoTextBounds.left + infoTextBounds.width / 2, infoTextBounds.top + infoTextBounds.height / 2);
  infoText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 30.f);
}

GameOverState::~GameOverState()
{
}

void GameOverState::handleEvent(const sf::Event &event)
{
  switch (event.type)
  {
  case sf::Event::KeyPressed:
    if (event.key.code == sf::Keyboard::Escape)
      changeState(new MainMenuState(window, states));
    break;

  default:
    break;
  }
}

void GameOverState::update(const float dt)
{
}

void GameOverState::render(sf::RenderTarget &target)
{
  target.draw(background);
  target.draw(mainText);
  target.draw(infoText);
}
