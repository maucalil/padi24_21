#ifndef PLAYER_GUI_HPP
#define PLAYER_GUI_HPP

#include "Entities/Player.hpp"
#include "GUI/ProgressBar.hpp"
#include "GUI/Container.hpp"

class PlayerGUI
{
private:
  Player *player;

  ProgressBar *hpBar;
  ProgressBar *expBar;

  Container *attributesContainer;

public:
  PlayerGUI(Player *player);
  ~PlayerGUI();

  void update(const float &dt);
  void render(sf::RenderTarget &target);
};

#endif