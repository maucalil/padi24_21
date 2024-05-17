#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
private:
  void initVariables();

public:
  Player(sf::Vector2f pos, sf::Texture* texture);
  ~Player();

  void updatePlayerPosition();
  void checkWindowCollision(const sf::RenderTarget* target);
  void update(const float dt, sf::RenderTarget *target);
};

#endif