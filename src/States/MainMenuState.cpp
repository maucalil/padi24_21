#include "States/MainMenuState.hpp"

void MainMenuState::addOption(std::string optionName)
{
  sf::Text option;
  option.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
  option.setString(optionName);

  sf::FloatRect textBounds = option.getGlobalBounds();
  option.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

  if (options.empty())
  {
    option.setPosition(window->getView().getSize() / 2.f);
  }
  else
  {
    auto &lastOptionPos = options.back().getPosition();
    option.setPosition(lastOptionPos.x, lastOptionPos.y + 40.f);
  }

  options.push_back(option);
}

void MainMenuState::updateOptionText()
{
  if (options.empty())
    return;

  for (auto &option : options)
  {
    option.setFillColor(sf::Color::White);
  }

  options[optionIndex].setFillColor(sf::Color::Blue);
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::stack<State *> *states)
    : State(window, states)
{
  sf::Vector2f windowSize = window->getView().getSize();

  background.setTexture(*ResourceManager::getTexture("world/background.jpeg"));

  sf::FloatRect backgroundBounds = background.getGlobalBounds();
  background.setOrigin(backgroundBounds.left + backgroundBounds.width / 2, backgroundBounds.top + backgroundBounds.height / 2);
  background.setPosition(windowSize / 2.f);
  background.setScale(windowSize.x / backgroundBounds.width, windowSize.y / backgroundBounds.height);

  title.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
  title.setCharacterSize(60);
  title.setString("Name In Progress");

  sf::FloatRect titleBounds = title.getGlobalBounds();
  title.setOrigin(titleBounds.left + titleBounds.width / 2, titleBounds.top + titleBounds.height / 2);

  title.setPosition(windowSize.x / 2.f, 60.f);

  optionIndex = 0;
  addOption("Play");
  addOption("Quit");
  updateOptionText();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::handleEvent(const sf::Event &event)
{
  switch (event.type)
  {
  case sf::Event::KeyPressed:
    if (event.key.code == sf::Keyboard::Escape)
    {
      break;
    }
    else if (event.key.code == sf::Keyboard::Up)
    {
      if (optionIndex > 0)
        optionIndex--;
      else
        optionIndex = options.size() - 1;

      updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
      if (optionIndex < options.size() - 1)
        optionIndex++;
      else
        optionIndex = 0;

      updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Return)
    {
      if (optionIndex == Play)
      {
        states->push(new GameState(window, states));
      }
      else if (optionIndex == Exit)
      {
        quit = true;
      }
    }

  default:
    break;
  }
}

void MainMenuState::update(const float dt)
{
  sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
}

void MainMenuState::render(sf::RenderTarget &target)
{
  target.draw(background);
  target.draw(title);
  
  for (auto &option : options)
  {
    target.draw(option);
  }
}
