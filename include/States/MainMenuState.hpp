#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "GUI/Button.hpp"
#include "States/State.hpp"
#include "States/GameState.hpp"

class MainMenuState : public State
{
private:
  enum OptionNames {
    Play,
    Exit,
  };

  sf::Text title;
  std::vector<sf::Text> options;
  std::size_t optionIndex;

  sf::Sprite background;
  sf::Music backgroundMusic;

  void addOption(std::string optionName);
  void updateOptionText();

  void initGUI();
  void initSounds();

public:
  MainMenuState(sf::RenderWindow *window, std::stack<State *> *states);
  ~MainMenuState();


  void handleEvent(const sf::Event &event);
  void update(const float dt);
  void render(sf::RenderTarget &target);
};
  
#endif