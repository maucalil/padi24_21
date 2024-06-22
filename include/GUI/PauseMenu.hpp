#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <SFML/Graphics.hpp>

#include "System/ResourceManager.hpp"

class PauseMenu
{
private:
    enum OptionNames {
    RESUME,
    EXIT,
  };

  sf::Text title;
  std::vector<sf::Text> options;
  int optionIndex;
  int optionPressed;
  

  sf::RectangleShape background;
  sf::Vector2f size;

  void addOption(std::string optionName);
  void updateOptionText();

public:
  PauseMenu(sf::Vector2f size, sf::Vector2f position);
  ~PauseMenu();
  
  bool resume();
  bool quit();

  //Functions
  void update(sf::Keyboard::Key key);
  void render(sf::RenderTarget & target);
};

#endif