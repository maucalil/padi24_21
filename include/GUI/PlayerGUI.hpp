#ifndef PLAYER_GUI_HPP
#define PLAYER_GUI_HPP

#include "Entities/Player.hpp"

class PlayerGUI
{
private:
  /* data */
public:
  PlayerGUI(Player* player);
  ~PlayerGUI();

  void update(const float& dt);
  void render(sf::RenderTarget& target);
};

#endif