#include "GUI/PauseMenu.hpp"

void PauseMenu::addOption(std::string optionName)
{
  sf::Text option;
  option.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
  option.setString(optionName);

  sf::FloatRect textBounds = option.getGlobalBounds();
  option.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

  if (options.empty())
  {
    option.setPosition(size.x / 2.f, size.y /2.f - 15.f);
  }
  else
  {
    auto &lastOptionPos = options.back().getPosition();
    option.setPosition(lastOptionPos.x, lastOptionPos.y + 40.f);
  }

  options.push_back(option);
}

void PauseMenu::updateOptionText()
{
  if (options.empty())
    return;

  for (auto &option : options)
  {
    option.setFillColor(sf::Color::White);
  }

  options[optionIndex].setFillColor(sf::Color(150, 150, 150, 200));
  optionPressed = -1;
}

PauseMenu::PauseMenu(sf::Vector2f size, sf::Vector2f position)
    : size(size)
{
  background.setFillColor(sf::Color(0, 0, 0, 150));
  background.setSize(size);
  background.setOrigin(size / 2.f);
  background.setPosition(position);


  title.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
  title.setCharacterSize(35);
  title.setString("Paused");

  sf::FloatRect titleBounds = title.getGlobalBounds();
  title.setOrigin(titleBounds.left + titleBounds.width / 2, titleBounds.top + titleBounds.height / 2);
  title.setPosition(size.x / 2.f, size.y / 2.f - 90.f);

  optionIndex = 0;
  optionPressed = -1;
  addOption("Resume");
  addOption("Quit");
  updateOptionText();
}

PauseMenu::~PauseMenu()
{
}

bool PauseMenu::resume()
{
  return optionPressed == RESUME;
}

bool PauseMenu::quit()
{
  return optionPressed == EXIT;
}

void PauseMenu::update(sf::Keyboard::Key key)
{
  if (key == sf::Keyboard::Up)
  {
    if (optionIndex > 0)
      optionIndex--;
    else
      optionIndex = options.size() - 1;

    updateOptionText();
  }
  else if (key == sf::Keyboard::Down)
  {
    if (optionIndex < options.size() - 1)
      optionIndex++;
    else
      optionIndex = 0;

    updateOptionText();
  } else if (key == sf::Keyboard::Return) {
    optionPressed = optionIndex;
  }
}

void PauseMenu::render(sf::RenderTarget &target)
{
  target.draw(background);
  target.draw(title);

  for (auto &option : options)
  {
    target.draw(option);
  }
}
